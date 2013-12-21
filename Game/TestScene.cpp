#include "TestScene.h"
#include <Tocs/Math/Constants.h>

namespace Tocs {

TestScene::TestScene(Rendering::RenderSystem &system)
: Table(system, Asset<Rendering::Mesh>::Load("table/table.obj"))
, OverheadLight(system, Math::Vector3(0, 2.5f, 0), 10, Math::Color(250,237,155))
, Sword(system, Asset<Rendering::Mesh>::Load("sword/sword.obj"))
, Apple(system, Asset<Rendering::Mesh>::Load("apple/apple.3ds"))
//, Book(system,  Asset<Rendering::Mesh>::Load("book/book_red.obj"))
, TableLight(system, Math::Vector3(0, 0.3, 0), 5, Math::Color(214,0,0))
, OtherLight(system, Math::Vector3(0, 0.3, 0.5), 20, Math::Color(0, 214, 0))
, OtherLight2 (system, Math::Vector3(0, 0.3, -0.5), 20, Math::Color(0, 0, 214))
{
	Table.GetMaterial(0).Source(Asset <Rendering::MaterialSource>::Load("table/table.mtl"));
	Table.Transform.Scale(0.5f, 0.5f, 0.5f);
	Table.Transform.Position(0, -2.77/2, 0);
	Table.Transform.CreateMatrix();
	Table.QueueJobs();

	Sword.GetMaterial(0).Source(Asset<Rendering::MaterialSource>::Load("sword/sword.mtl"));
	Sword.Transform.Scale(0.5f, 0.5f, 0.5f);
	Sword.Transform.Rotation = Math::Quaternion::FromEuler(Math::Constants::Pi<float>() / 2,0 * Math::Constants::Pi<float>() / 4, 0);
	Sword.Transform.Position(-0.8f, 0.075f, 0);
	Sword.Transform.CreateMatrix();
	Sword.QueueJobs();

	Apple.GetMaterial(0).Source(Asset <Rendering::MaterialSource>::Load("apple/apple.mtl"));
	Apple.Transform.Position(1, 0.1f, 0);
	Apple.Transform.CreateMatrix();
	Apple.QueueJobs();
	//
	//Book.GetMaterial(0).Source(Asset <Rendering::MaterialSource>::Load("book/book_red.mtl"));
	//Book.Transform.Position(0.5f, 0.08f, 0.5f);
	//Book.Transform.Scale(1.3f, 1.3f, 1.3f);
	//Book.Transform.CreateMatrix();
	//Book.QueueJobs();
}

void TestScene::Update(float dt)
{
	static float t = 0; t += dt;
	OtherLight.Transform.Position(cos(t) * 0.5f, 0.3f, sin(t) * 0.5f);
	OtherLight2.Transform.Position(cos(t + Math::Constants::Pi<float>()) * 0.5f, 0.3f, sin(t + Math::Constants::Pi<float>()));
}

}