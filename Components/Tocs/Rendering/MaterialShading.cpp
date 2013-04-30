#include "MaterialShading.h"

namespace Tocs {
namespace Rendering {

void MaterialShadingType::AddShaders (Graphics::Shader &targetshader) const
{
	targetshader.AddCode(Template.Get().GetShader (MatShading->Values));
}

}}