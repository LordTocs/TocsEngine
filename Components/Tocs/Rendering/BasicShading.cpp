#include "BasicShading.h"


namespace Tocs {
namespace Rendering {

BasicShadingType LoadFromFile (const std::string &file)
{
	BasicShadingType result;

	result.ImportShader(Asset<Graphics::ShaderCode>::Load(file)); //I'm cheap, deal with it.

	return std::move(result);
}

void BasicShadingType::ImportShader(Asset<Graphics::ShaderCode> shader)
{
	Shaders.push_back(shader);
}

void BasicShadingType::AddShaders(Graphics::Shader &targetshader) const
{
	for (auto i = Shaders.begin(); i != Shaders.end (); ++i)
	{
		targetshader.AddCode((*i).Get ());
	}
}



}}