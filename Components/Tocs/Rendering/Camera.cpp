#include "Camera.h"

using namespace Tocs::Math;
using namespace Tocs::Graphics;

namespace Tocs {
namespace Rendering {

Camera::Camera (float ar)
	: FoV (90),
	  Up (0,1,0),
	  AspectRatio (ar)
{
	ProjectionMatrix = Matrix4::CreateProjection (FoV,AspectRatio,0.001f,1000.0f);
}

void Camera::Compute ()
{
	ViewMatrix = Matrix4::CreateLookAt (Position,LookAt,Up);
}

void Camera::PassToShader (Shader &shader) const
{
	shader["View"] = ViewMatrix;
	shader["Projection"] = ProjectionMatrix;
}



}}