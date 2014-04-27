#include "Game.h"
#include <cmath>
#include <cstdlib>
#include <Tocs/MeshTools/Primitives.h>
#include <Tocs/Rendering/ShaderPermutationTemplate.h>
#include <Tocs/Rendering/ShaderPermutationInput.h>

namespace Tocs {

Game::Game ()
	: Window ("Tocs Engine",1920,1080,false,false),
	  GContext (Window),
	  RenderSystem (GContext),
	  Camera (Window.GetWidth(), Window.GetHeight()),
	  CameraController(Camera,Window.Input),
	  Pause(false)
{
	GContext.SetClearDepth(1000);
	GContext.EnableDepthTest();
	GContext.EnableDepthWrite();
	GContext.EnableBackfaceCulling();
	GContext.SetClearColor(Math::Color(0, 0, 0));
}


void Game::Start()
{
	while (!Window.IsExiting ())
	{
		Window.PumpMessages();
		//GContext.ClearActiveBuffer();
		float dt = GameTick.GetTickTime();
		Update(dt);
		Window.Input.Update(dt);
		Render(dt);
		GContext.FlipToScreen();
	}
}

void Game::Update(float dt)
{
	Math::TransformArbitor::Global.Get().ComputeTransformationMatricies();
	static float t = 0;
	CameraController.Update(dt);
	Camera.Compute();
	
	if (!Pause)
	{
		RenderSystem.Update(dt);
	}
	
	if (Window.Input.Keyboard.IsNewlyPressed(Input::Key::P))
	{
		RenderSystem.GetShadows().DebugSave("debug/Shadows");
	}

	if (Window.Input.Keyboard.IsNewlyPressed(Input::Key::O))
	{
		//RenderSystem.GetAntiAliasing().OutputDebugImages();
		RenderSystem.GetPostProcesses().Glow.OutputDebugImages("debug/glow");
	}
	if (Window.Input.Keyboard.IsNewlyPressed(Input::Key::I))
	{
		RenderSystem.UseSMAA = !RenderSystem.UseSMAA;
	}
	if (Window.Input.Keyboard.IsNewlyPressed(Input::Key::U))
	{
		Pause = !Pause;
	}

	t += dt;
}

void Game::Render(float dt)
{
	RenderSystem.Render(Camera);
}

}