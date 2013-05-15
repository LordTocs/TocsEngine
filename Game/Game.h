#pragma once
#include <Tocs/Core/Ticker.h>

#include <Tocs/Graphics/SimpleWindow.h>
#include <Tocs/Rendering/RenderSystem.h>
#include <Tocs/Rendering/Camera.h>
#include <Tocs/Rendering/Model.h>
#include <Tocs/Rendering/PointLight.h>
#include "FreeCameraController.h"
#include "TileGrid.h"


namespace Tocs {

class Game
{
	Graphics::SimpleWindow Window;
	Graphics::GraphicsContext GContext;
	Rendering::RenderSystem RenderSystem;
	Ticker GameTick;

	Rendering::Camera Camera;
	FreeCameraController CameraController;

	Rendering::PointLight Light1;
	Rendering::PointLight Light2;

	std::unique_ptr<Rendering::Model> FloorModel;
	TileGrid TestGrid;
public:
	Game();

	void Update (float dt);
	void Render (float dt);

	void Start ();
};

}