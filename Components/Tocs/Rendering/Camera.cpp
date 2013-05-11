#include "Camera.h"
#include <Tocs/Math/Constants.h>
using namespace Tocs::Math;
using namespace Tocs::Graphics;

namespace Tocs {
namespace Rendering {

Camera::Camera (int width, int height)
	: FoV (Constants::Pi<float> ()/2),
	  Up (0,1,0),
	  AspectRatio (static_cast<float>(width)/static_cast<float>(height)),
	  Width(width),
	  Height(height)
{
	ProjectionMatrix = Matrix4::CreateProjection (FoV,AspectRatio,0.001f,100.0f);
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