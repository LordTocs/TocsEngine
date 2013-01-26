#pragma once
#include <Tocs/Graphics/Shader.h>
#include "GeometryHandler.h"
#include <map>


namespace Tocs {
namespace Rendering {


class ShaderPool
{
	std::map<std::pair<GeometryHandler *, int>, Graphics::Shader> Shaders;
public:
	Graphics::Shader &GetShader (GeometryHandler &geom, Graphics::ShaderCode &pixelshader);

	static ShaderPool Global;
};

}}