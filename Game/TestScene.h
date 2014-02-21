#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Rendering/RenderSystem.h>
#include <Tocs/Rendering/Light.h>
#include <Tocs/Rendering/StaticMesh.h>
#include <Tocs/Rendering/Material.h>

#include <Tocs/Rendering/ParticleSystem.h>

namespace Tocs {

class TestScene
{
public:
	
	
	//Rendering::Light TableLight;
	//Rendering::Light OverheadLight;
	Rendering::Light OtherLight;
	//Rendering::Light OtherLight2;
	Rendering::Light CandleLight;


	Rendering::StaticMesh Apple;
	Rendering::StaticMesh Book;
	Rendering::StaticMesh Table;
	Rendering::StaticMesh Sword;
	Rendering::StaticMesh Vial;
	Rendering::StaticMesh Flask;
	Rendering::StaticMesh Crystal;
	Rendering::StaticMesh OpenScroll;
	Rendering::StaticMesh Candle;
	Rendering::StaticMesh CandleHolder;

	//Rendering::ParticleSystem TestParticles;

	TestScene(Rendering::RenderSystem &system);
	void Update(float dt);
};

}