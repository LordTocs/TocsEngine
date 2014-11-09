#include "Game.h"
#include <cmath>
#include <cstdlib>
#include <Tocs/MeshTools/Primitives.h>
#include <Tocs/Rendering/ShaderPermutationTemplate.h>
#include <Tocs/Rendering/ShaderPermutationInput.h>
#include <Tocs/Rendering/DebugDraw.h>

namespace Tocs {

	Game::Game()
		: Window("Tocs Engine", 1000, 1000, false, false),
		GContext(Window),
		RenderSystem(GContext),
		Camera(Window.GetWidth(), Window.GetHeight()),
		CameraController(Camera, Window.Input),
		Pause(false),
		Model(RenderSystem, Asset<Animation::AnimatedMesh>::Load("balrog/balrog.dae"))
	{
		GContext.SetClearDepth(1000);
		GContext.EnableDepthTest();
		GContext.EnableDepthWrite();
		GContext.EnableBackfaceCulling();
		GContext.SetClearColor(Math::Color(0, 0, 0));

		Model.GetMaterial(0).Source(Asset <Rendering::MaterialSource>::Load("balrog/balrog.mtl"));
		Model.QueueJobs();

		

	}


	void Game::Start()
	{
		while (!Window.IsExiting())
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
		static float t = 0;

		for (int b = 0; b < Model.Armature().BoneCount(); ++b)
		{
			Model.Armature()[b].Transform.Rotation() = Model.Armature()[b].DefaultPose().RealPart * Math::Quaternion::FromEuler(std::sin(t) * 0.3f, 0, 0);
		}

		Math::TransformArbitor::Global.Get().ComputeTransformationMatricies();
		
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
		RenderSystem.Render(dt, Camera);
	}

}