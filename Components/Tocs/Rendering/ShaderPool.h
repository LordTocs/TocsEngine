#pragma once
#include <Tocs/Graphics/Shader.h>
#include <map>
#include "Geometry.h"
#include "Shading.h"

namespace Tocs {
namespace Rendering {


class ShaderPool
{
	std::map<std::pair<const GeometryType *, const ShadingType *>, Graphics::Shader> Shaders;
public:
	Graphics::Shader &GetShader (const Geometry &geometry,const Shading &shading);

	static ShaderPool Global;
};

}}