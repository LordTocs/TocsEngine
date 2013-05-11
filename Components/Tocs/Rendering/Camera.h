#pragma once
#include <Tocs/Math/Matrix4.h>
#include <Tocs/Math/Vector3.h>
#include <Tocs/Graphics/Shader.h>
namespace Tocs {
namespace Rendering {

class Camera
{
	Math::Matrix4 ViewMatrix;
	Math::Matrix4 ProjectionMatrix;

	float FoV;
	float AspectRatio;
public:
	int Width, Height;

	Math::Vector3 Position;
	Math::Vector3 LookAt;
	Math::Vector3 Up;
	
	Camera(int width, int height);

	const Math::Matrix4 &GetView () const { return ViewMatrix; }
	const Math::Matrix4 &GetProjection () const { return ProjectionMatrix; }

	void Compute ();
	void PassToShader (Graphics::Shader &shader) const;
};

}}