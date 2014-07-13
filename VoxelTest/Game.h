#pragma once
#include <Tocs/Core/Ticker.h>

#include <Tocs/Input/SimpleWindow.h>
#include <Tocs/Rendering/RenderSystem.h>
#include <Tocs/Rendering/Camera.h>
//#include <Tocs/Animation/AnimatedModel.h>
#include <Tocs/Rendering/StaticMesh.h>
#include <Tocs/Voxels/Chunk.h>

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

		Voxels::Chunk Chunk;
		std::unique_ptr<Rendering::StaticMesh> VoxelModel;
		Rendering::Light Light1;
		Rendering::Light Light2;
		Rendering::Light Light3;


		bool Pause;
	public:
		Game();
		Game(const Game &) = delete;

		void Update(float dt);
		void Render(float dt);

		void Start();
	};

}