/*#include "Game.h"
#include <cmath>
#include <cstdlib>
#include <Tocs/Rendering/Primitives.h>

namespace Tocs {

Game::Game ()
	: Window ("Tocs Engine",1000,1000,false,false),
	  GContext (Window),
	  RenderSystem (GContext),
	  Camera (Window.GetWidth(), Window.GetHeight()),
	  CameraController(Camera,Window.Input),
	  Light1(RenderSystem),
	  Light2(RenderSystem)
	  //TestGrid(10,10)
{
	GContext.SetClearDepth(1000);
	GContext.EnableDepthTest();
	GContext.EnableDepthWrite();

	//Rendering::RenderInitList ().Init ();

	Camera.Position(0,1.65f,0);

	Light1.Transform.Position(7,0,0);
	Light1.Radius = 40;
	Light1.Show();

	Light2.Transform.Position(8,5,8);
	Light2.Color = Math::Color(255,193,122);
	Light2.Radius = 20;
	Light2.Intensity = 1;
	Light2.Show();
	/*
	for (int i = 0; i < 10; ++i)
	{
		TestGrid(i,5).Type = TileType::Air;
		TestGrid(i,4).Type = TileType::Air;
		TestGrid(5,i).Type = TileType::Air;
		TestGrid(4,i).Type = TileType::Air;
	}*/
	/*
	for (int x = 0; x < 16; ++x)
	{
		for (int y = 0; y < 16; ++y)
		{
			Chunk.Get(Math::Vector3i(x,0,y)).Info.Fill = 31;
			int h = ((x > 6 && x <= 12) && (y > 6 && y <= 12)) ? 2 : 1;
			Chunk.Get(Math::Vector3i(x,h,y)).Info.Fill = x*2;//std::rand () % 30 + 1;
			Chunk.Get(Math::Vector3i(x,h,y)).Info.Direction = 2;
			Chunk.Get(Math::Vector3i(x,h-1,y)).Info.Fill = 31;

			Chunk.Get(Math::Vector3i(x,6,y)).Info.Fill = 31;
			int h2 = ((x > 6 && x <= 12) && (y > 6 && y <= 12)) ? 4 : 5;
			Chunk.Get(Math::Vector3i(x,h2,y)).Info.Fill = x*2;//std::rand () % 30 + 1;
			Chunk.Get(Math::Vector3i(x,h2,y)).Info.Direction = Voxels::Direction::Down.Index();
			Chunk.Get(Math::Vector3i(x,h2+1,y)).Info.Fill = 31;
		}
	}

	//for (int i = 0; i < 10; ++i)
	//{
	//	Chunk.Get(Math::Vector3i(8,i,8)).Info.Fill = 31;
	//}
	//Chunk.Get(Math::Vector3i(8,10,8)).Info.Fill = 16;
	//Chunk.Get(Math::Vector3i(8,10,8)).Info.Direction = 2;


	Chunk.GenerateMesh ();

	MeshModel = std::unique_ptr<Rendering::Model> (new Rendering::Model(Asset<Rendering::Mesh>::Wrap(*Chunk.GeneratedMesh.get()),RenderSystem));
	MeshModel->Materials[0].SetMaterial(Asset<Rendering::Material>::Load("Vox.mtl"));
	MeshModel->Transform.Position(-8,0,-8);
	MeshModel->Show();

	//MeshModel = std::unique_ptr<Rendering::Model> (new Rendering::Model(Asset<Rendering::Mesh>::Load("sword/sword.obj"),RenderSystem));
	//MeshModel->Materials[0].SetMaterial(Asset<Rendering::Material>::Load("sword/sword.mtl"));
	//MeshModel->Transform.Position(0,0,0);
	//MeshModel->Show();



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

	static float t = 0;
	t += dt;
	Light2.Transform.Position (cos(t) * 5,3.5f,sin(t) * 5);
}

void Game::Render(float dt)
{
	RenderSystem.Update(dt);
	RenderSystem.Render(GContext,Camera);
}

}*/