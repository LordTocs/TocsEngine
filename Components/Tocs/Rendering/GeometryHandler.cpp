#include "GeometryHandler.h"
#include <Tocs/Graphics/Shader.h>
using namespace Tocs::Graphics;

namespace Tocs {
namespace Rendering {

GeometryHandler::GeometryHandler()
	: VertexShader (ShaderType::Vertex)
{
}
void GeometryHandler::AddToShader (Graphics::Shader &shader)
{
	shader.AddCode(VertexShader);
}
}}