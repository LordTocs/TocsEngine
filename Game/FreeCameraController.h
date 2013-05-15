#pragma once
#include <Tocs/Rendering/Camera.h>
#include <Tocs/Input/InputManager.h>
#include <Tocs/Math/Constants.h>
namespace Tocs {

class FreeCameraController
{
	Rendering::Camera &Camera;
	Input::InputManager &CameraInput;

	float Pitch, Yaw;

	unsigned int LockX;
	unsigned int LockY;

public:
	FreeCameraController (Rendering::Camera &camera, Input::InputManager &input)
		: Camera(camera),
	      CameraInput(input),
		  CameraSpeed(5),
		  RotationalSpeed(0.1f),
		  Pitch(),Yaw(Math::Constants::Pi<float>()/2)
	{}
	float CameraSpeed;
	float RotationalSpeed;

	void Update (float dt);
	

};

}

