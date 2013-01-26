#include "ShaderPool.h"

namespace Tocs {
namespace Rendering {

ShaderPool ShaderPool::Global;

Graphics::Shader &ShaderPool::GetShader (GeometryHandler &geom, Graphics::ShaderCode &pixelshader)
{
	std::pair <GeometryHandler *,int> key (&geom,pixelshader.GetID ());
	auto i = Shaders.find(key);
	if (i == Shaders.end ())
	{
		Graphics::Shader shader;
		shader.AddCode (pixelshader);
		geom.AddToShader(shader);
		shader.Link ();

		auto result = Shaders.insert (std::make_pair (key,std::move(shader)));
		i = result.first;
	}

	return (*i).second;
}

}}