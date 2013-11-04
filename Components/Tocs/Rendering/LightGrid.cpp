#include "LightGrid.h"
#include <Tocs/Math/Vector2i.h>
#include <algorithm>

namespace Tocs {
namespace Rendering {


static void UpdateClipRegionRoot (float nc, float lc, float lz, float radius, float camerascale, float &clipmin, float &clipmax)
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

static void UpdateClipRegion (float lc, float lz, float radius, float camerascale, float &clipmin, float &clipmax)
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
static Math::Vector4 ComputeClipRegion (Math::Vector3 pos, float radius, float cnear,const Math::Matrix4 &projection)
{
	Math::Vector4 region (1.0f,1.0f,-1.0f,-1.0f);
	if (pos.Z - radius <= -cnear)
	{
		Math::Vector2 clipmin(-1.0f, -1.0f);
		Math::Vector2 clipmax( 1.0f,  1.0f);

		UpdateClipRegion (pos.X,pos.Z,radius,projection(1,1),clipmin.X,clipmax.X);
		UpdateClipRegion (pos.Y,pos.Z,radius,projection(2,2),clipmin.Y,clipmax.Y);

		region(clipmin.X,clipmin.Y,clipmax.X,clipmax.Y);
	}

	return region;
}

static Math::Vector4i ClipToScreenSpace (Math::Vector4 cliprect, const Camera &camera)
{
	cliprect *= -1;

	std::swap (cliprect.X, cliprect.Z);
	std::swap (cliprect.Y, cliprect.W);
	cliprect *= 0.5f;
	cliprect += Math::Vector4 (0.5f,0.5f,0.5f,0.5f);


	static const Math::Vector4 zeros (0.0f,0.0f,0.0f,0.0f);
	static const Math::Vector4 ones (1.0f,1.0f,1.0f,1.0f);

	cliprect = Clamp (cliprect,zeros,ones);

	Math::Vector4i result;
	result.X = int(cliprect.X * float(camera.Width));
	result.Y = int(cliprect.Y * float(camera.Height));
	result.Z = int(cliprect.Z * float(camera.Width));
	result.W = int(cliprect.W * float(camera.Height));

	return result;

}

void LightGrid::Configure (const Camera &camera, const std::vector<Light*> &lights)
{
	std::vector<Math::Vector4i> screenspacelights;

	//Find screenspace lights
	for (auto i = lights.begin (); i != lights.end(); ++i)
	{
		Math::Vector3 viewspace = camera.GetView() * (*i)->Transform.GetWorldPosition ();

		Math::Vector4i screenspace = ClipToScreenSpace (ComputeClipRegion (viewspace,(*i)->Radius,camera.Near,camera.GetProjection ()),camera);

		if (screenspace.X < screenspace.Z && screenspace.Y < screenspace.W)
		{
			screenspacelights.push_back(screenspace);
		}
	}

	//Count each tile's

	int totallightentries = 0;

	for (auto i = screenspacelights.begin (); i != screenspacelights.end (); ++i)
	{
		Math::Vector2i min ((*i).X,(*i).Y);
		Math::Vector2i max ((*i).Z,(*i).W);

		min = Clamp (min / TileSize, Math::Vector2i(0,0), Math::Vector2i (GridSize.X + 1, GridSize.Y + 1));
		max = Clamp (Math::Vector2i (max.X + TileSize - 1,max.Y + TileSize - 1) / TileSize, Math::Vector2i(0,0), Math::Vector2i (GridSize.X + 1, GridSize.Y + 1));

		for (unsigned int y = min.Y; y < max.Y; ++y)
		{
			for (unsigned int x = min.X; x < min.X; ++x)
			{
				CountsAndOffsets (x,y).X += 1;
				++totallightentries;
			}
		}
	}

	unsigned int offset = 0;
	for (unsigned int y = 0; y < GridSize.Y; ++y)
	{
		for (unsigned int x = 0; x < GridSize.X; ++x)
		{
			unsigned count = CountsAndOffsets (x,y).X;
			CountsAndOffsets(x,y).Y = offset + count;
			offset += count;
		}
	}

	//Allocate mores space if necessary
	if (LightIndexListsCPU.size () < totallightentries)
	{
		LightIndexListsCPU.resize(totallightentries);
	}

	//Insert light ID's
	for (auto i = screenspacelights.begin (); i != screenspacelights.end (); ++i)
	{
		Math::Vector2i min ((*i).X,(*i).Y);
		Math::Vector2i max ((*i).Z,(*i).W);

		min = Clamp (min / TileSize, Math::Vector2i(0,0), Math::Vector2i (GridSize.X + 1, GridSize.Y + 1));
		max = Clamp (Math::Vector2i (max.X + TileSize - 1,max.Y + TileSize - 1) / TileSize, Math::Vector2i(0,0), Math::Vector2i (GridSize.X + 1, GridSize.Y + 1));

		for (unsigned int y = min.Y; y < max.Y; ++y)
		{
			for (unsigned int x = min.X; x < min.X; ++x)
			{
				unsigned int offset = CountsAndOffsets(x,y).X - 1;
				LightIndexListsCPU[offset] = i - screenspacelights.begin();
				CountsAndOffsets(x,y).X = offset;
			}
		}
	}

	//Copy to buffers
	Grid.Write (CountsAndOffsetsCPU.get(),GridSize.X * GridSize.Y);
	if (LightIndexLists.Size () < LightIndexListsCPU.size())
	{
		LightIndexLists.Build (LightIndexListsCPU.size());
	}
	LightIndexLists.Write(LightIndexListsCPU);

	//Write lights

}



}}