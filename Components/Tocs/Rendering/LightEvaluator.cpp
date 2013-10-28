#include "LightEvaluator.h"

namespace Tocs {
namespace Rendering {

LightEvaluator::LightEvaluator (RenderSystem &system, Graphics::GraphicsContext &context)
	: TilesWide (context.GetTarget().GetWidth()/8), TilesHigh (context.GetTarget().GetHeight()/8),
	  EvaluationShader (Asset<Graphics::ShaderCode>::Load("TileShadingEvaluator.frag"))
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

}}
