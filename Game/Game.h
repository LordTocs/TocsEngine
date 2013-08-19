#pragma once
#include <Tocs/Core/Ticker.h>

#include <Tocs/Input/SimpleWindow.h>
#include <Tocs/Rendering/RenderSystem.h>
#include <Tocs/Rendering/Camera.h>
#include <Tocs/Rendering/Model.h>
#include <Tocs/Rendering/PointLight.h>
#include <Tocs/Voxels/Chunk.h>


#include "FreeCameraController.h"
#include "TileGrid.h"


namespace Tocs {

class Game
{
	Input::SimpleWindow Window;
	Graphics::GraphicsContext GContext;
	Rendering::RenderSystem RenderSystem;
	Ticker GameTick;

	Rendering::Camera Camera;
	FreeCameraController CameraController;

	Rendering::PointLight Light1;
	Rendering::PointLight Light2;

	std::unique_ptr<Rendering::Model> MeshModel;
	//TileGrid TestGrid;

	Voxels::Chunk Chunk;
public:
	Game();

	void Update (float dt);
	void Render (float dt);

	void Start ();
};

}