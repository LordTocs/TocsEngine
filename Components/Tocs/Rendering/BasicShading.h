#pragma once
#include <Tocs/Core/Asset.h>
#include "Shading.h"
#include <Tocs/Graphics/Shader.h>
#include <Tocs/Graphics/UniformMap.h>
#include <vector>

namespace Tocs {
namespace Rendering {

class BasicShadingType : public ShadingType
{
	std::vector<Asset<Graphics::ShaderCode>> Shaders;
public:
	void ImportShader (Asset<Graphics::ShaderCode> shader);
	void AddShaders (Graphics::Shader &targetshader) const;

	static BasicShadingType LoadFromFile (const std::string &file);
};

class BasicShading : public Shading
{
	Graphics::UniformMap Uniforms;
	const BasicShadingType &Type;
public:
	BasicShading(const BasicShadingType &type)
		: Type (type)
	{}

	const ShadingType &GetType () const { return Type; }

	Graphics::UniformMap::UniformValue &operator[] (const std::string &name)
	{ return Uniforms[name]; }

	void PassToShader (Graphics::Shader &shader, const Camera &cam) const
	{ Uniforms.PassToShader(shader); }
};

}}