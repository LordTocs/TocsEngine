#include "Game.h"
#include <cmath>
#include <cstdlib>
#include <Tocs/MeshTools/Primitives.h>

namespace Tocs {

Game::Game ()
	: Window ("Tocs Engine",1000,1000,false,false),
	  GContext (Window),
	  RenderSystem (GContext),
	  Camera (Window.GetWidth(), Window.GetHeight()),
	  CameraController(Camera,Window.Input),
	  LightBox(RenderSystem, Asset<Rendering::Mesh>::Wrap(MeshTools::Primitives::Cube.Get())), //
	  Scene(RenderSystem)
{


	GContext.SetClearDepth(1000);
	GContext.EnableDepthTest();
	GContext.EnableDepthWrite();
	GContext.SetClearColor(Math::Color(128, 128, 128));


	Asset<Rendering::MaterialSource> mat = Asset<Rendering::MaterialSource>::Load("crystal/wire.mtl");

	LightBox.GetMaterial(0).Source(mat);

	LightBox.Transform.Position(0, 2.5, 0);
	LightBox.Transform.Scale(10, 10, 10);
	LightBox.Transform.CreateMatrix();

	LightBox.QueueJobs();
}


void Game::Start()
{
	while (!Window.IsExiting ())
	{
		Window.PumpMessages();
		//GContext.ClearActiveBuffer();
		float dt = GameTick.GetTickTime();
		Window.Input.Update(dt);
		Update(dt);
		Render(dt);
		GContext.FlipToScreen();
	}
}

void Game::Update(float dt)
{
	static float t = 0;
	CameraController.Update(dt);
	Camera.Compute();

	
	t += dt;
}

void Game::Render(float dt)
{
	RenderSystem.Update(dt);
	RenderSystem.Render(GContext,Camera);
}

}