#pragma once
#include <Tocs/Graphics/ShaderCode.h>

namespace Tocs {
namespace Rendering {

class GeometryHandler
{
	Graphics::ShaderCode VertexShader;
public:
	GeometryHandler();
	GeometryHandler(GeometryHandler &&moveme);

	Graphics::ShaderCode &GetCode () { return VertexShader; }
	
	virtual void AddToShader (Graphics::Shader &shader);

	static GeometryHandler LoadFromFile (const std::string &filename);

};

}}