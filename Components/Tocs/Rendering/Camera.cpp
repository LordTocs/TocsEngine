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
	  Near(0.01f),
	  Far(1000.0f),
	  Width(width),
	  Height(height)
{
	ComputeProjection();
}

void Camera::ComputeProjection()
{
	ProjectionMatrix = Matrix4::CreateProjection(FoV, AspectRatio, Near, Far);
	InverseProjectionMatrix = Matrix4::Inversion(ProjectionMatrix);
}

void Camera::Compute ()
{
	ViewMatrix = Matrix4::CreateLookAt (Position,LookAt,Up);
	InverseViewMatrix = Matrix4::Inversion(ViewMatrix);
}

void Camera::PassToShader (Shader &shader) const
{
	shader["View"] = ViewMatrix;
	shader["Projection"] = ProjectionMatrix;
}

void Camera::SetUpViewport(Graphics::GraphicsContext &context) const
{
	context.Viewport(Width, Height);
}

}}