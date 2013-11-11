#pragma once
#include <Tocs/Math/Matrix4.h>
#include <Tocs/Math/Vector.h>
#include <Tocs/Graphics/Shader.h>
namespace Tocs {
namespace Rendering {

class Camera
{
	Math::Matrix4 ViewMatrix;
	Math::Matrix4 ProjectionMatrix;
	Math::Matrix4 InverseProjectionMatrix;

	float FoV;
	float AspectRatio;

public:
	int Width, Height;
	float Near;
	float Far;

	Math::Vector3 Position;
	Math::Vector3 LookAt;
	Math::Vector3 Up;
	
	Camera(int width, int height);

	const Math::Matrix4 &GetView () const { return ViewMatrix; }
	const Math::Matrix4 &GetProjection () const { return ProjectionMatrix; }
	const Math::Matrix4 &GetInverseProjection () const { return InverseProjectionMatrix; }

	void Compute ();
	void PassToShader (Graphics::Shader &shader) const;

	Math::Vector3 Direction () const { return (LookAt - Position).Normalized(); }
};

}}