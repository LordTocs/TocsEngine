#include "ShadowManager.h"
#include "RenderSystem.h"
#include <Tocs/Drawing/Image.h>
#include <sstream>

namespace Tocs {
namespace Rendering {


ShadowManager::ShadowManager(RenderSystem &system)
: PointLights(10)
, ShadowMapSize(1024)
, PointLightShadows(PointLights, ShadowMapSize, Graphics::TextureFormat::Shadow32, Graphics::TextureFiltering::None)
, ShadowCamera(ShadowMapSize, ShadowMapSize)
{
}

struct ScreenLight
{
public:
	Light *light;
	int ScreenSpace;

	ScreenLight(Light *l, int s)
		: light(l), ScreenSpace(s) {}

	bool operator< (const ScreenLight &other)
	{
		return ScreenSpace < other.ScreenSpace; 
	}
};

//Assign shadow maps based on screen size of light?
void ShadowManager::AssignShadowMaps(RenderSystem &system)
{
	std::vector<ScreenLight> screenlights;

	for (auto &l : system.GetLights())
	{
		if (!l->Visible())
		{
			continue;
		}
		l->ShadowMap(-1);
		screenlights.push_back(ScreenLight(l, l->ScreenSpace())) ;
	}

	std::sort(screenlights.begin(), screenlights.end());

	int ShadowIndex = 0;
	for (int i = 0; i < PointLights && i < screenlights.size(); ++i)
	{
		if (screenlights[i].light->Shadows)
		{
			screenlights[i].light->ShadowMap(ShadowIndex++);
			GenerateShadowMap(system, *screenlights[i].light);
		}
	}

	//DebugSave("debug/Shadows");
}

void ShadowManager::GenerateShadowMap(RenderSystem &system, Light &light)
{
	static Math::Vector3 CubeDirections[] =
	{ 
		Math::Vector3( 1, 0, 0),
		Math::Vector3(-1, 0, 0),
		Math::Vector3( 0, 1, 0),
		Math::Vector3( 0,-1, 0),
		Math::Vector3( 0, 0, 1), 
		Math::Vector3( 0, 0,-1), 
	};

	static Math::Vector3 CubeUps[] =
	{ 
		Math::Vector3( 0,-1, 0),
		Math::Vector3( 0,-1, 0),
		Math::Vector3( 0, 0, 1),
		Math::Vector3( 0, 0,-1),
		Math::Vector3( 0,-1, 0),
		Math::Vector3( 0,-1, 0), 
	};

	if (light.ShadowMap() == -1)
		return;

	ShadowCamera.Near = 0.01;
	ShadowCamera.Far = light.Radius;
	ShadowCamera.Position = light.Transform.GetWorldPosition();
	ShadowCamera.ComputeProjection();

	for (int face = 0; face < 6; ++face)
	{
		ShadowTarget.SetDepthCubeMapArraySide(PointLightShadows, light.ShadowMap(), face);

		ShadowCamera.LookAt = light.Transform.GetWorldPosition() + CubeDirections[face];
		ShadowCamera.Up = CubeUps[face];
		ShadowCamera.Compute();


		ShadowCamera.SetUpViewport(system.Context());
		ShadowTarget.Bind();
		system.Context().ClearDepth();
		system.Pipes.ShadowPipe.Draw(ShadowCamera);
		ShadowTarget.UnBind();
	}
}


void ShadowManager::DebugSave(const std::string &fileprefix) const
{
	int size = PointLightShadows.GetSize();
	int layers = PointLightShadows.GetLayers();
	Drawing::Image img(size, size);
	std::unique_ptr<float[]> depthdata(new float[size*size * 6 * layers]);

	PointLightShadows.Read(depthdata.get(), Graphics::TextureDataFormat::DepthFloat);

	for (int l = 0; l < layers; ++l)
	{
		for (int f = 0; f < 6; ++f)
		{
			int offset = ((l * 6) + f) * (size * size);
			for (int y = 0; y < size; ++y)
			{
				for (int x = 0; x < size; ++x)
				{
					float depth = depthdata[offset + y * size + x];
					depth = (2 * ShadowCamera.Near) / (10.0f + ShadowCamera.Near - depth * (10.0f - ShadowCamera.Near));
					img(x, y) = Math::Color((depth)* 255, (depth)* 255, (depth)* 255, 255);
				}
			}


			std::stringstream ss;
			ss << fileprefix << l << "_" << f << ".png";
			img.WriteToFile(ss.str());
		}
	}
}

}}