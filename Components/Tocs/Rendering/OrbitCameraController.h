#pragma once
#include "Camera.h"
#include <Tocs/Core/Numerics.h>
#include <cmath>
namespace Tocs {
namespace Rendering {

class OrbitCameraController
{
	Camera &ControlledCamera;
	float Pitch;
	float Yaw;
	float Zoom;
public:
	OrbitCameraController(Camera &camera)
		: ControlledCamera(camera),
		  Pitch(), Yaw(), Zoom(10)
	{}

	void DoZoom (float amount)
	{
		Zoom += amount;
		Zoom = Clamp(Zoom,1.0f,150.0f);
	}

	void DoPitch (float amount)
	{
		Pitch += amount;
		Pitch = Clamp (Pitch,-3.14159f/2 + 0.001f,3.14159f/2 - 0.001f);
	}

	void DoYaw (float amount)
	{
		Yaw += amount;
	}

	void Calculate ()
	{
		ControlledCamera.Position = ControlledCamera.LookAt + Math::Vector3 (cos(Yaw)*cos(Pitch),sin(Pitch), sin(Yaw)*cos(Pitch)) * Zoom;
	}


};

}}