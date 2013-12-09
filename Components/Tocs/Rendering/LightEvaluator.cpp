#include "LightEvaluator.h"


namespace Tocs {
namespace Rendering {

LightEvaluator::LightEvaluator ()
	:  EvaluationShader (Asset<Graphics::ShaderCode>::Load("TileShadingEvaluator.frag"))
{
}


void LightEvaluator::LinkShaderCode (ShaderConstruction &construction) const
{
	construction.AddCode (EvaluationShader.Get());
}

}}
