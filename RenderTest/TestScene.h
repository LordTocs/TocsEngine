#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Rendering/RenderSystem.h>
#include <Tocs/Rendering/Light.h>
#include <Tocs/Rendering/StaticMesh.h>
#include <Tocs/Rendering/Material.h>
#include <Tocs/Animation/AnimatedMesh.h>
#include <Tocs/Rendering/ParticleSystem.h>

namespace Tocs {

class TestScene
{
public:
	
	
	//Rendering::Light TableLight;
	//Rendering::Light OverheadLight;
	Rendering::Light OtherLight;
	Rendering::Light OtherLight2;
	Rendering::Light CandleLight;
	Rendering::Light MagicLight;
	Rendering::Light TorchLight;


	Rendering::StaticMesh Apple;
	Rendering::StaticMesh Book;
	Rendering::StaticMesh Mushrooms;
	Rendering::StaticMesh Table;
	Rendering::StaticMesh Sword;
	Rendering::StaticMesh Vial;
	Rendering::StaticMesh Flask;
	Rendering::StaticMesh Crystal;
	Rendering::StaticMesh OpenScroll;
	Rendering::StaticMesh Candle;
	Rendering::StaticMesh CandleHolder;

	Rendering::StaticMesh Corner0;
	Rendering::StaticMesh Corner1;
	Rendering::StaticMesh Corner2;
	Rendering::StaticMesh Corner3;

	Rendering::ParticleSystem TestParticles;

	Rendering::StaticMesh Torch;
	Rendering::ParticleSystem TorchFlame;

	TestScene(Rendering::RenderSystem &system);
	void Update(float dt);
};

}