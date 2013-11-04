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



void LightEvaluator::Configure (const Camera &camera, const std::vector<Light *> &lights)
{
	/*std::vector<ScreenRectangle> lightrects;
	std::vector<Math::Vector4> viewspacelights;

	for (auto i = lights.begin(); i != lights.end (); ++i)
	{
		Light *light = (*i);
		Math::Vector3 viewspace = camera.GetView() * light->Transform.GetWorldPosition ();
		
		Math::Vector4 clipspacerect = ComputeClipRegion (viewspace,light->Radius,camera.Near,camera.Far);
		clipspacerect *= 0.5f;
		clipspacerect += Math::Vector4(0.5f,0.5f,0.5f,0.5f);

		ScreenRectangle rect;
		

		
	}*/


}

}}
