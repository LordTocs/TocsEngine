#pragma once
#include <Tocs/Core/Ticker.h>

#include <Tocs/Input/SimpleWindow.h>
#include <Tocs/Rendering/RenderSystem.h>
#include <Tocs/Rendering/Camera.h>
#include <Tocs/Animation/AnimatedModel.h>


#include "FreeCameraController.h"

namespace Tocs {

	class Game
	{
		Input::SimpleWindow Window;
		Graphics::GraphicsContext GContext;
		Rendering::RenderSystem RenderSystem;
		Ticker GameTick;

		Rendering::Camera Camera;
		FreeCameraController CameraController;

		Animation::AnimatedModel Model;

		bool Pause;
	public:
		Game();
		Game(const Game &) = delete;

		void Update(float dt);
		void Render(float dt);

		void Start();
	};

}