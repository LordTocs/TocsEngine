#include "ShaderPool.h"

namespace Tocs {
namespace Rendering {

ShaderPool ShaderPool::Global;

Graphics::Shader &ShaderPool::GetShader (const Geometry &geometry, const Shading &shading)
{
	std::pair <const GeometryType *,const ShadingType *> key (&geometry.GetType (), &shading.GetType ());
	auto i = Shaders.find(key);
	if (i == Shaders.end ())
	{
		Graphics::Shader shader;
		geometry.GetType ().AddShaders (shader);
		shading.GetType().AddShaders (shader);
		shader.Link ();

		auto result = Shaders.insert (std::make_pair (key,std::move(shader)));
		i = result.first;
	}
	return (*i).second;
}

}}