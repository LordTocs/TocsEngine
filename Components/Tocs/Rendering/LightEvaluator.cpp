#include "LightEvaluator.h"
#include <Tocs/Math/Vector3.h>

namespace Tocs {
namespace Rendering {

LightEvaluator::LightEvaluator (RenderSystem &system, Graphics::GraphicsContext &context)
	:  EvaluationShader (Asset<Graphics::ShaderCode>::Load("TileShadingEvaluator.frag")),
	   LightGrid (64*64),
	   LightIndexLists(1),
	   LightIndexListsTexture (LightIndexLists,Graphics::TextureFormat::R32i),
	   PositionRange (1000),
	   ColorBuffer (1000)
{
}


/*Job LightEvaluator::CreatePrepassJob (Geometry &geometry, Pipeline &pipeline)
{
	ShaderConstruction construction;
	geometry.LinkShaders(construction,false);
}*/

void LightEvaluator::LinkShaderCode (ShaderConstruction &construction)
{
	construction.AddCode (EvaluationShader.Get());
}


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

void Configure (const Camera &camera, const std::vector<Light *> &lights)
{
	
}

}}
