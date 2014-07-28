#include "FreeCameraController.h"
#include <Tocs/Math/Util.h>
#include <Tocs/Math/Constants.h>
#include <Tocs/Math/Vector.h>
#include <cmath>
using namespace Tocs::Math;

namespace Tocs {

void FreeCameraController::Update (float dt)
{
	Vector3 dir = Camera.Direction();

	if (CameraInput.Keyboard.IsPressed(Input::Key::W)) //w
	{
		Camera.Position += dir * dt * CameraSpeed;
	}
	if (CameraInput.Keyboard.IsPressed(Input::Key::S)) //s
	{
		Camera.Position -= dir * dt * CameraSpeed;
	}
	if (CameraInput.Keyboard.IsPressed(Input::Key::A)) //a
	{
		Camera.Position -= (dir.Cross(Camera.Up)).Normalized() * dt * CameraSpeed;
	}
	if (CameraInput.Keyboard.IsPressed(Input::Key::D)) //d
	{
		Camera.Position -= (Camera.Up.Cross(dir)).Normalized() * dt * CameraSpeed;
	}

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
		Pitch = Clamp (Pitch,-Constants::Pi<float>()/2 + 0.001f,Constants::Pi<float>()/2 - 0.001f);
		Yaw += dx;

		//std::cout << "P: " << Pitch << ", Y: " << Yaw << std::endl;
	}

	if (CameraInput.Mouse.Left.IsNewlyUp())
	{
		CameraInput.Mouse.Show();
	}


	Camera.LookAt = Camera.Position + Vector3(std::cos(Yaw)*std::cos(Pitch),std::sin(Pitch),std::sin(Yaw)*std::cos(Pitch));

	//std::cout << Camera.Position << ", " << (Camera.LookAt) << std::endl;
}


}