#include "Light.h"
#include "RenderSystem.h"
#include <Tocs/Math/Util.h>
namespace Tocs {
namespace Rendering {

Light::Light(RenderSystem &system)
: System(system), Radius(1), Intensity(1), Color(255, 255, 255), Shadows(true)
{
	system.Add(*this);
}

Light::Light(RenderSystem &system, Math::Vector3 position, float radius, Math::Color color)
: System(system), Transform(position), Radius(radius), Color(color), Intensity(1), Shadows(true)
{
	system.Add(*this);
}

Light::~Light()
{
	System.Remove(*this);
}

//Screenspace stuff

static void UpdateClipRegionRoot(float nc, float lc, float lz, float radius, float camerascale, float &clipmin, float &clipmax)
{
	float nz = (radius - nc * lc) / lz;
	float pz = (lc * lc + lz * lz - radius * radius) / (lz - (nz / nc) * lc);

	if (pz < 0.0f)
	{
		float c = -nz * camerascale / nc;
		if (nc < 0.0f)
		{
			// Left side boundary
			clipmin = std::max(clipmin, c);
		}
		else
		{
			// Right side boundary
			clipmax = std::min(clipmax, c);
		}
	}
}

static void UpdateClipRegion(float lc, float lz, float radius, float camerascale, float &clipmin, float &clipmax)
{
	float rSq = radius * radius;
	float lcSqPluslzSq = lc * lc + lz * lz;
	float d = rSq * lc * lc - lcSqPluslzSq * (rSq - lz * lz);

	if (d >= 0.0f)
	{
		float a = radius * lc;
		float b = sqrt(d);
		float nx0 = (a + b) / lcSqPluslzSq;
		float nx1 = (a - b) / lcSqPluslzSq;

		UpdateClipRegionRoot(nx0, lc, lz, radius, camerascale, clipmin, clipmax);
		UpdateClipRegionRoot(nx1, lc, lz, radius, camerascale, clipmin, clipmax);
	}
}

//Computes a clipspace bounding box of a sphere.
static Math::Vector4 ComputeClipRegion(Math::Vector3 pos, float radius, float cnear, const Math::Matrix4 &projection)
{
	Math::Vector4 region(1.0f, 1.0f, -1.0f, -1.0f);
	if (pos.Z - radius <= -cnear) //In front of the camera?
	{
		Math::Vector2 clipmin(-1.0f, -1.0f);
		Math::Vector2 clipmax(1.0f, 1.0f);

		UpdateClipRegion(pos.X, pos.Z, radius, projection(0, 0), clipmin.X, clipmax.X);
		UpdateClipRegion(pos.Y, pos.Z, radius, projection(1, 1), clipmin.Y, clipmax.Y);

		region(clipmin.X, clipmin.Y, clipmax.X, clipmax.Y);
	}

	return region;
}

void Light::ComputeScreenRect(const Camera &cam)
{
	Math::Vector3 viewspace = cam.GetView() * Transform.GetWorldPosition();

	Math::Vector4 clipregion = ComputeClipRegion(viewspace, Radius, cam.Near, cam.GetProjection());

	clipregion *= -1;

	std::swap(clipregion.X, clipregion.Z);
	std::swap(clipregion.Y, clipregion.W);

	//(maxx,maxy,minx,miny)

	clipregion *= 0.5f;
	clipregion += Math::Vector4(0.5f, 0.5f, 0.5f, 0.5f);


	static const Math::Vector4 zeros(0.0f, 0.0f, 0.0f, 0.0f);
	static const Math::Vector4 ones(1.0f, 1.0f, 1.0f, 1.0f);

	clipregion = Math::Clamp(clipregion, zeros, ones);

	if (clipregion.X < clipregion.Z && clipregion.Y < clipregion.W)
	{
		ScreenRect = Math::BoundingBox2Di::MinMax(
		Math::Vector2i(int(clipregion.X * float(cam.Width)),
					   int(clipregion.Y * float(cam.Height))),
		Math::Vector2i(int(clipregion.Z * float(cam.Width)),
					   int(clipregion.W * float(cam.Height))));
	}
	else
	{
		ScreenRect.Width(0);
		ScreenRect.Height(0);
	}

}

bool Light::Visible() const
{
	return ScreenRect.Width() != 0;
}

}}