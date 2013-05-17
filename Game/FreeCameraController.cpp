#include "FreeCameraController.h"
#include <cmath>
using namespace Tocs::Math;

namespace Tocs {

void FreeCameraController::Update (float dt)
{
	Vector3 dir = Camera.Direction();

	if (CameraInput.Keyboard.IsPressed(0x57)) //w
	{
		Camera.Position += dir * dt * CameraSpeed;
	}
	if (CameraInput.Keyboard.IsPressed(0x53)) //s
	{
		Camera.Position -= dir * dt * CameraSpeed;
	}
	if (CameraInput.Keyboard.IsPressed(0x41)) //a
	{
		Camera.Position -= Vector3::Normalized (dir.Cross(Camera.Up)) * dt * CameraSpeed;
	}
	if (CameraInput.Keyboard.IsPressed(0x44)) //d
	{
		Camera.Position -= Vector3::Normalized (Camera.Up.Cross(dir)) * dt * CameraSpeed;
	}


	//if (CameraInput.Mouse.IsLeftButtonNewlyDown ())
	//{
	//	LockX = CameraInput.Mouse.X;
	//	LockY = CameraInput.Mouse.Y;
	//	CameraInput.Mouse.Hide();
	//}

	if (CameraInput.Mouse.Left.IsNewlyDown ())
	{
		LockX = CameraInput.Mouse.X();
		LockY = CameraInput.Mouse.Y();
		CameraInput.Mouse.Hide();
	}

	if (CameraInput.Mouse.Left.IsDown())
	{
		float dx = CameraInput.Mouse.DeltaX()  * dt * RotationalSpeed;
		float dy = CameraInput.Mouse.DeltaY()  * dt * RotationalSpeed;
		//std::cout << "Delta: " << dx << ", " << dy << std::endl;
		
		CameraInput.Mouse.SetPosition(LockX,LockY);

		Pitch -= dy;
		Yaw += dx;

		//std::cout << "P: " << Pitch << ", Y: " << Yaw << std::endl;
	}

	if (CameraInput.Mouse.Left.IsNewlyUp())
	{
		CameraInput.Mouse.Show();
	}


	Camera.LookAt = Camera.Position + Vector3(std::cos(Yaw)*std::cos(Pitch),std::sin(Pitch),std::sin(Yaw)*std::cos(Pitch));
}


}