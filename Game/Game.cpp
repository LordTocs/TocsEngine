#include "Game.h"
#include <Tocs/Rendering/Primitives.h>
#include <Tocs/Rendering/Init.h>
namespace Tocs {

Game::Game ()
	: Window ("Tocs Engine",1000,1000,false,false),
	  GContext (Window),
	  RenderSystem (GContext),
	  Camera (Window.GetWidth(), Window.GetHeight()),
	  CameraController(Camera,Window.Input),
	  //LittleBox (Asset<Rendering::Mesh>::Wrap(Rendering::Primitives::Cube.Get()),RenderSystem),
	  //BigBox (Asset<Rendering::Mesh>::Wrap(Rendering::Primitives::Cube.Get()),RenderSystem),
	  Light1(RenderSystem),
	  Light2(RenderSystem),
	  TestGrid(10,10)
{
	GContext.SetClearDepth(1000);
	GContext.EnableDepthTest();
	GContext.EnableDepthWrite();

	//Rendering::RenderInitList ().Init ();

	Camera.Position(0,1.65f,0);

	//LittleBox.Transform.Position(0,0.5,0);
	//LittleBox.Materials[0].SetMaterial(Asset<Rendering::Material>::Load("Crate.mtl"));
	//LittleBox.Show();
	//
	//BigBox.Transform.Position(0,-2.5,0);
	//BigBox.Transform.Scale(5,5,5);
	//BigBox.Materials[0].SetMaterial(Asset<Rendering::Material>::Load("Crate.mtl"));
	//BigBox.Show();

	Light1.Transform.Position(0,1,0);
	Light1.Radius = 20;
	Light1.Show();

	Light2.Transform.Position(3,1,0);
	Light2.Color = Math::Color(0,0,255);
	Light2.Radius = 2;
	Light2.Intensity = 10;
	Light2.Show();
	
	for (int i = 0; i < 10; ++i)
	{
		TestGrid(i,5).Type = TileType::Air;
		TestGrid(i,4).Type = TileType::Air;
		TestGrid(5,i).Type = TileType::Air;
		TestGrid(4,i).Type = TileType::Air;
	}

	FloorModel = std::unique_ptr<Rendering::Model> (new Rendering::Model(Asset<Rendering::Mesh>::Manage("Floor",new Rendering::Mesh(std::move(TestGrid.GenerateMesh()))),RenderSystem));
	FloorModel->Materials[0].SetMaterial(Asset<Rendering::Material>::Load("Floor.mtl"));
	FloorModel->Transform.Position(-5,0,-5);
	FloorModel->Show();

}


void Game::Start()
{
	while (!Window.IsExiting ())
	{
		Window.PumpMessages();
		GContext.ClearActiveBuffer();
		float dt = GameTick.GetTickTime();
		Window.Input.Update(dt);
		Update(dt);
		Render(dt);
		GContext.FlipToScreen();
	}
}

void Game::Update(float dt)
{
	
	CameraController.Update(dt);
	Camera.Compute();
}

void Game::Render(float dt)
{
	RenderSystem.Update(dt);
	RenderSystem.Render(GContext,Camera);
}

}