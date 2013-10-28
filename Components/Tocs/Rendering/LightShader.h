#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/ShaderCode.h>
#include <Tocs/Graphics/UniformMap.h>
#include "ShaderPool.h"
#include <vector>
namespace Tocs {
namespace Rendering {



class LightShader
{
	//Must supply Shade (vec4 LightDir, vec4 ViewDir, vec4 LightColor, float Attenuation)
	std::vector<Asset<Graphics::ShaderCode>> Sources;
	std::vector<Asset<Graphics::Texture2D>> Textures;
	bool Transparency;
	
	LightShader(const LightShader &);
public:
	LightShader () : Transparency (false) {}

	Graphics::UniformMap Inputs;

	static LightShader LoadFromFile (const std::string &filename);

	bool HasTransparency () const { return Transparency; }

	void LinkShaderCode (ShaderConstruction &construction);
};

}}
