#include "Game.h"
#include <cmath>
#include <cstdlib>
#include <Tocs/MeshTools/Primitives.h>
#include <Tocs/Rendering/ShaderPermutationTemplate.h>
#include <Tocs/Rendering/ShaderPermutationInput.h>

namespace Tocs {

Game::Game ()
	: Window ("Tocs Engine",1000,1000,false,false),
	  GContext (Window),
	  RenderSystem (GContext),
	  Camera (Window.GetWidth(), Window.GetHeight()),
	  CameraController(Camera,Window.Input),
	  Scene(RenderSystem)
{
	GContext.SetClearDepth(1000);
	GContext.EnableDepthTest();
	GContext.EnableDepthWrite();
	GContext.EnableBackfaceCulling();
	GContext.SetClearColor(Math::Color(128, 128, 128));
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
	Scene.Update(dt);
	
	t += dt;
}

void Game::Render(float dt)
{
	RenderSystem.Update(dt);
	RenderSystem.Render(Camera);
}

}