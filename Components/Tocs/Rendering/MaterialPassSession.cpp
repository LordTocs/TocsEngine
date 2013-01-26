#include "MaterialPassSession.h"

namespace Tocs {
namespace Rendering {

MaterialPassSession::MaterialPassSession(Graphics::Shader &shader)
	: BoundShader (shader)
{
}


MaterialPassSession::~MaterialPassSession(void)
{
	BoundShader.UnBind ();
} 

void MaterialPassSession::SetCamera (const Camera &cam)
{
	BoundShader["View"] = cam.GetView ();
	BoundShader["Projection"] = cam.GetProjection ();
}
void MaterialPassSession::SetTransform (const Math::Transform &transform)
{
	BoundShader["World"] = transform.GetMatrix ();
}

}}