#pragma once
#include <Tocs/Core/Ticker.h>

#include <Tocs/Input/SimpleWindow.h>
#include <Tocs/Rendering/RenderSystem.h>
#include <Tocs/Rendering/Camera.h>


#include "FreeCameraController.h"
#include "TileGrid.h"
#include "TestScene.h"
#include <Tocs/Rendering/Light.h>

#include <Tocs/Rendering/StaticMesh.h>
#include <Tocs/Rendering/Material.h>


namespace Tocs {

class Game
{
	Input::SimpleWindow Window;
	Graphics::GraphicsContext GContext;
	Rendering::RenderSystem RenderSystem;
	Ticker GameTick;

	Rendering::Camera Camera;
	FreeCameraController CameraController;

	TestScene Scene;
	Rendering::StaticMesh LightBox;
public:
	Game();
	Game(const Game &) = delete;

	void Update (float dt);
	void Render (float dt);

	void Start ();
};

}