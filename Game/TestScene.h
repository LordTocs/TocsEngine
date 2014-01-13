#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Rendering/RenderSystem.h>
#include <Tocs/Rendering/Light.h>
#include <Tocs/Rendering/StaticMesh.h>
#include <Tocs/Rendering/Material.h>

namespace Tocs {

class TestScene
{
public:
	
	Rendering::Light OverheadLight;
	//Rendering::Light TableLight;
	//Rendering::Light OtherLight;
	Rendering::Light OtherLight2;


	Rendering::StaticMesh Apple;
	Rendering::StaticMesh Book;
	Rendering::StaticMesh Table;
	Rendering::StaticMesh Sword;
	Rendering::StaticMesh Vial;
	Rendering::StaticMesh Flask;
	Rendering::StaticMesh Crystal;

	TestScene(Rendering::RenderSystem &system);
	void Update(float dt);
};

}