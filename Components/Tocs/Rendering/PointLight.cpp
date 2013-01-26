#include "PointLight.h"

namespace Tocs {
namespace Rendering {

PointLight::PointLight(float size)
	: PointLightShader(Asset<Graphics::Shader>::Load("PointLight.shd")),
	  Job (this),
	  Size (size),
	  Color (255,255,255)
{
}

PointLight::PointLight(float size, const Math::Color &color)
	: PointLightShader(Asset<Graphics::Shader>::Load("PointLight.shd")),
	  Job (this),
	  Size (size),
	  Color (color)
{
}



}}