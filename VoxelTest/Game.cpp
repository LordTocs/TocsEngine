#include "Game.h"
#include <cmath>
#include <cstdlib>
#include <Tocs/MeshTools/Primitives.h>
#include <Tocs/Rendering/ShaderPermutationTemplate.h>
#include <Tocs/Rendering/ShaderPermutationInput.h>
#include <Tocs/Rendering/DebugDraw.h>
#include <random>

namespace Tocs {

	Game::Game()
		: Window("Tocs Engine", 1000, 1000, false, false),
		GContext(Window),
		RenderSystem(GContext),
		Camera(Window.GetWidth(), Window.GetHeight()),
		CameraController(Camera, Window.Input),
		Pause(false),
		Light1(RenderSystem, Math::Vector3(5, 5, 5), 16.0f, Math::Color(250, 237, 155))
		//Light2(RenderSystem, Math::Vector3(5, 5, 5), 16.0f, Math::Color(255, 255, 255)),
		//Light3(RenderSystem, Math::Vector3(5, 5, 5), 16.0f, Math::Color(255, 255, 255))
	{
		GContext.SetClearDepth(1000);
		GContext.EnableDepthTest();
		GContext.EnableDepthWrite();
		GContext.EnableBackfaceCulling();
		GContext.SetClearColor(Math::Color(0, 0, 0));

		std::random_device rd;

		std::default_random_engine rand(rd());

		std::uniform_int_distribution<unsigned int> fill (1, 16);

		for (int y = 0; y < 16; ++y)
		{
			for (int x = 0; x < 16; ++x)
			{
				Chunk.Get(x, 0, y).SetDirection(Voxels::Direction::Up);
				Chunk.Get(x, 0, y).Info.Fill = fill(rand);
				Chunk.Get(x, 4, y).SetDirection(Voxels::Direction::Down);
				Chunk.Get(x, 4, y).Info.Fill = fill(rand);
			}
		}

		Chunk.Get(8, 0, 8).Set(31, Voxels::Direction::Up);
		Chunk.Get(8, 4, 8).Set(31, Voxels::Direction::Down);
		Chunk.Get(8, 1, 8).Set(31, Voxels::Direction::Up);
		Chunk.Get(7, 1, 8).Set(fill(rand), Voxels::Direction::Left);
		Chunk.Get(9, 1, 8).Set(fill(rand), Voxels::Direction::Right);
		Chunk.Get(8, 1, 7).Set(fill(rand), Voxels::Direction::Backward);
		Chunk.Get(8, 1, 9).Set(fill(rand), Voxels::Direction::Forward);

		Chunk.Get(8, 2, 8).Set(31, Voxels::Direction::Up);
		Chunk.Get(7, 2, 8).Set(fill(rand), Voxels::Direction::Left);
		Chunk.Get(9, 2, 8).Set(fill(rand), Voxels::Direction::Right);
		Chunk.Get(8, 2, 7).Set(fill(rand), Voxels::Direction::Backward);
		Chunk.Get(8, 2, 9).Set(fill(rand), Voxels::Direction::Forward);

		Chunk.Get(8, 3, 8).Set(31, Voxels::Direction::Up);
		Chunk.Get(7, 3, 8).Set(fill(rand), Voxels::Direction::Left);
		Chunk.Get(9, 3, 8).Set(fill(rand), Voxels::Direction::Right);
		Chunk.Get(8, 3, 7).Set(fill(rand), Voxels::Direction::Backward);
		Chunk.Get(8, 3, 9).Set(fill(rand), Voxels::Direction::Forward);

		//Chunk.Get(8, 0, 8).Set(1.0, Voxels::Direction::Up);
		//Chunk.Get(7, 0, 8).Set(0.4, Voxels::Direction::Up);
		//Chunk.Get(8, 0, 7).Set(1.0, Voxels::Direction::Up);
		//Chunk.Get(7, 0, 7).Set(0.4, Voxels::Direction::Up);
		

		Chunk.GenerateMesh();

		VoxelModel.reset(new Rendering::StaticMesh(RenderSystem, Asset<Rendering::Mesh>::Wrap(*Chunk.GeneratedMesh.get())));

		VoxelModel->GetMaterial(0).Source(Asset <Rendering::MaterialSource>::Load("voxel.mtl"));
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
		Math::Vector3 orbitcenter(8, 2.5f, 8);
		Light1.Transform.Position() = Math::Vector3(std::cos(t), 0, std::sin(t)) * 5.0f + orbitcenter;
		//Light2.Transform.Position() = Math::Vector3(std::cos(t + 2 *Math::Constants::Pi<float>() / 3), 0, std::sin(t + 2 * Math::Constants::Pi<float>() / 3)) * 5.0f + orbitcenter;
		//Light3.Transform.Position() = Math::Vector3(std::cos(t + 4 * Math::Constants::Pi<float>() / 3), 0, std::sin(t + 4 * Math::Constants::Pi<float>() / 3)) * 5.0f + orbitcenter;


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
		RenderSystem.Render(dt,Camera);
	}

}