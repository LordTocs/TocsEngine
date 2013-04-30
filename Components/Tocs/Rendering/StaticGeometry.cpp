#include "StaticGeometry.h"


namespace Tocs {
namespace Rendering {

void StaticGeometryType::ImportShader(Asset<Graphics::ShaderCode> shader)
{
	Shaders.push_back(shader);
}

void StaticGeometryType::AddShaders(Graphics::Shader &targetshader) const
{
	for (auto i = Shaders.begin(); i != Shaders.end (); ++i)
	{
		targetshader.AddCode((*i).Get ());
	}
}

StaticGeometryType StaticGeometryType::LoadFromFile (const std::string &filename)
{
	StaticGeometryType result;

	result.ImportShader(Asset<Graphics::ShaderCode>::Load(filename)); //YEY LAZY

	return std::move(result);
}

}}