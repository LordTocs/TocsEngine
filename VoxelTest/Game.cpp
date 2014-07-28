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
		Pause(false)
	{
		GContext.SetClearDepth(1000);
		GContext.EnableDepthTest();
		GContext.EnableDepthWrite();
		GContext.EnableBackfaceCulling();
		GContext.SetClearColor(Math::Color(0, 0, 0));

		for (int y = 0; y < 16; ++y)
		{
			for (int x = 0; x < 16; ++x)
			{
				Chunk.Get(x, 0, y).SetDirection(Voxels::Direction::Up);
				Chunk.Get(x, 0, y).Info.Fill = 1;
			}
		}

		Chunk.Get(8, 0, 8).Set(1.0, Voxels::Direction::Up);
		Chunk.Get(8, 1, 8).Set(1.0, Voxels::Direction::Up);

		Chunk.Get(7, 1, 8).Set(0.4f, Voxels::Direction::Left);
		Chunk.Get(9, 1, 8).Set(0.4f, Voxels::Direction::Right);
		Chunk.Get(8, 1, 7).Set(0.4f, Voxels::Direction::Backward);
		Chunk.Get(8, 1, 9).Set(0.4f, Voxels::Direction::Forward);

		Chunk.Get(8, 2, 8).Set(0.2f, Voxels::Direction::Up);
		

		Chunk.GenerateMesh();

		VoxelModel.reset(new Rendering::StaticMesh(RenderSystem, Asset<Rendering::Mesh>::Wrap(*Chunk.GeneratedMesh.get())));

		VoxelModel->GetMaterial(0).Source(Asset <Rendering::MaterialSource>::Load("wire.mtl"));
		VoxelModel->QueueJobs();

	}


	void Game::Start()
	{
		while (!Window.IsExiting())
		{
			Window.PumpMessages();
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

		Math::TransformArbitor::Global.Get().ComputeTransformationMatricies();
		
		CameraController.Update(dt);
		Camera.Compute();

		Math::Vector3 offset(8.5f, 1.5f, 8.5f);
		Rendering::DebugDraw::Line(offset, Math::Vector3(0, 0.5f, 0) + offset, Math::Color(0, 255, 0));
		Rendering::DebugDraw::Line(offset, Math::Vector3(0.5f, 0, 0) + offset, Math::Color(255, 0, 0));
		Rendering::DebugDraw::Line(offset, Math::Vector3(0, 0, 0.5f) + offset, Math::Color(0, 0, 255));

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
		RenderSystem.Render(Camera);
	}

}