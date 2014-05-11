#include "TestScene.h"
#include <Tocs/Math/Constants.h>

namespace Tocs {

TestScene::TestScene(Rendering::RenderSystem &system)
: Table(system, Asset<Rendering::Mesh>::Load("table/table.3ds"))
, Sword(system, Asset<Rendering::Mesh>::Load("sword/sword.obj"))
, Apple(system, Asset<Rendering::Mesh>::Load("apple/apple.3ds"))
, Vial(system, Asset<Rendering::Mesh>::Load("vial/vial.3ds"))
, Flask(system, Asset<Rendering::Mesh>::Load("vial/flask.3ds"))
, Book(system, Asset<Rendering::Mesh>::Load("book/book.3ds"))
, OpenScroll(system, Asset<Rendering::Mesh>::Load("scrolls/OpenScroll.3ds"))
, Candle(system, Asset<Rendering::Mesh>::Load("candle/candle.3ds"))
, CandleHolder(system, Asset<Rendering::Mesh>::Load("candle/holder.3ds"))
, Crystal(system, Asset<Rendering::Mesh>::Load("crystal/crystal.3ds"))
, Mushrooms(system, Asset<Rendering::Mesh>::Load("mushroom/mushroom.3ds"))
//, TableLight(system, Math::Vector3(0, 0.3, 0), 10, Math::Color(214,0,0))
//, OverheadLight(system, Math::Vector3(0, 2.4f, 0), 10, Math::Color(250, 237, 155))
, OtherLight(system, Math::Vector3(0, 0.3, 0.5), 10, Math::Color(250, 237, 155))
, OtherLight2(system, Math::Vector3(0, 0.3, -0.5), 10, Math::Color(250, 237, 155))
, MagicLight(system, Math::Vector3(0, 0, 0), 5, Math::Color(0,255,0))
, CandleLight(system, Math::Vector3(0.5f, 0.38f, -0.25f), 4, Math::Color(250, 237, 155))
, TestParticles(system, Asset<Rendering::ParticleSystemSource>::Load("magic/magic.particle"))
, TorchFlame(system, Asset<Rendering::ParticleSystemSource>::Load("torch/flame.particle"))
, TorchLight(system, Math::Vector3(), 10, Math::Color(255, 107, 0))
, Torch(system, Asset<Rendering::Mesh>::Load("torch/Torch.3ds"))
, Corner0(system, Asset<Rendering::Mesh>::Load("dungeon/corner.3ds"))
, Corner1(system, Asset<Rendering::Mesh>::Load("dungeon/corner.3ds"))
, Corner2(system, Asset<Rendering::Mesh>::Load("dungeon/corner.3ds"))
, Corner3(system, Asset<Rendering::Mesh>::Load("dungeon/corner.3ds"))
{
	Asset<Animation::AnimatedMesh> amesh = Asset<Animation::AnimatedMesh>::Load("balrog/balrog.dae");


	TestParticles.Transform().Position()(0, 1.0f, 0);
	TestParticles.QueueJobs();

	MagicLight.Transform.Parent(TestParticles.Transform());
	MagicLight.Shadows = false;

	for (int i = 0; i < Torch.MaterialCount(); ++i)
	{
		Torch.GetMaterial(i).Source(Asset<Rendering::MaterialSource>::Load("dungeon/dungeon.mtl"));
	}
	Torch.Transform.Position()(-5.1f, 2.0f, 0);
	Torch.QueueJobs();

	TorchFlame.Transform().Position()(0.68012, 0.70606, 0);
	TorchFlame.Transform().Parent(Torch.Transform);
	TorchFlame.QueueJobs();

	TorchLight.Transform.Position()(0, 0.2f, 0);
	TorchLight.Transform.Parent(TorchFlame.Transform());

	OtherLight.Intensity = 0.5f;
	OtherLight2.Intensity = 0.5f;
	//OtherLight.Shadows = false;
	//OverheadLight.Intensity = 0.1f;

	Table.GetMaterial(0).Source(Asset <Rendering::MaterialSource>::Load("table/table.mtl"));
	Table.Transform.Scale()(0.75f, 0.75f, 0.75f);
	//Table.Transform.Position(0, -2.77/2, 0);
	Table.Transform.CreateMatrix();
	Table.QueueJobs();

	Sword.GetMaterial(0).Source(Asset<Rendering::MaterialSource>::Load("sword/sword.mtl"));
	Sword.Transform.Scale()(0.5f, 0.5f, 0.5f);
	Sword.Transform.Rotation() = Math::Quaternion::FromEuler(Math::Constants::Pi<float>() / 2,0 * Math::Constants::Pi<float>() / 4, 0);
	Sword.Transform.Position()(-0.8f, 0.075f, 0);
	Sword.QueueJobs();

	OpenScroll.GetMaterial(0).Source(Asset<Rendering::MaterialSource>::Load("scrolls/scroll.mtl"));
	OpenScroll.Transform.Scale()(0.5f, 0.5f, 0.5f);
	OpenScroll.Transform.Position()(0.5f, 0.025f, 0.0f);
	OpenScroll.QueueJobs();

	Candle.GetMaterial(0).Source(Asset<Rendering::MaterialSource>::Load("candle/candle.mtl"));
	Candle.Transform.Scale()(1.0f, 1.0f, 1.0f);
	Candle.Transform.Position()(0.5f, 0.02f, -0.25f);
	Candle.Transform.Rotation() = Math::Quaternion::FromEuler(0,-Math::Constants::Pi<float>()/2, 0);
	Candle.QueueJobs();

	CandleHolder.GetMaterial(0).Source(Asset<Rendering::MaterialSource>::Load("candle/holder.mtl"));
	CandleHolder.Transform.Scale()(1.0f, 1.0f, 1.0f);
	CandleHolder.Transform.Position()(0.5f, 0.02f, -0.25f);
	CandleHolder.QueueJobs();

	Apple.GetMaterial(0).Source(Asset <Rendering::MaterialSource>::Load("apple/apple.mtl"));
	Apple.Transform.Position()(1, 0.1f, 0);
	//Apple.Transform.Parent(OtherLight2.Transform);
	//Apple.Transform.Position()(0, 0.5f, 0);
	Apple.QueueJobs();

	Vial.GetMaterial(0).Source(Asset <Rendering::MaterialSource>::Load("vial/vial.mtl"));
	Vial.Transform.Position()(0.5f, 0.14f, 0.5f);
	Vial.QueueJobs();

	Flask.GetMaterial(0).Source(Asset <Rendering::MaterialSource>::Load("vial/vial.mtl"));
	Flask.Transform.Position()(0.5f, 0.13f, -0.5f);
	Flask.QueueJobs();

	Crystal.GetMaterial(0).Source(Asset <Rendering::MaterialSource>::Load("crystal/rock.mtl"));
	Crystal.GetMaterial(1).Source(Asset <Rendering::MaterialSource>::Load("crystal/crystal.mtl"));
	Crystal.Transform.Position()(/*0.5f*/0, 0.2f, 0);
	Crystal.QueueJobs();

	//
	Book.GetMaterial(0).Source(Asset <Rendering::MaterialSource>::Load("book/book_red.mtl"));
	Book.Transform.Position()(-0.5f, 0.08f, 0.5f);
	Book.Transform.Scale()(1.3f, 1.3f, 1.3f);
	Book.QueueJobs();

	Mushrooms.GetMaterial(0).Source(Asset <Rendering::MaterialSource>::Load("mushroom/mushroom.mtl"));
	Mushrooms.GetMaterial(1).Source(Asset <Rendering::MaterialSource>::Load("mushroom/mushroom.mtl"));
	Mushrooms.GetMaterial(2).Source(Asset <Rendering::MaterialSource>::Load("mushroom/mushroom.mtl"));
	Mushrooms.GetMaterial(3).Source(Asset <Rendering::MaterialSource>::Load("mushroom/dirt.mtl"));
	Mushrooms.GetMaterial(4).Source(Asset <Rendering::MaterialSource>::Load("mushroom/pot.mtl"));
	Mushrooms.Transform.Position()(-1.0f, 0, 0);
	Mushrooms.Transform.Scale()(1.0f, 1.0f, 1.0f);
	Mushrooms.QueueJobs();

	for (int i = 0; i < Corner0.MaterialCount(); ++i)
	{
		Corner0.GetMaterial(i).Source(Asset<Rendering::MaterialSource>::Load("dungeon/dungeon.mtl"));
	}
	Corner0.Transform.Position()(2.5f, -0.75f, 2.5f);
	Corner0.QueueJobs();

	for (int i = 0; i < Corner0.MaterialCount(); ++i)
	{
		Corner1.GetMaterial(i).Source(Asset<Rendering::MaterialSource>::Load("dungeon/dungeon.mtl"));
	}
	Corner1.Transform.Position()(-2.5f, -0.75f, 2.5f);
	Corner1.Transform.Rotation() = Math::Quaternion::FromEuler(0, -Math::Constants::Pi<float>() / 2, 0);
	Corner1.QueueJobs();

	for (int i = 0; i < Corner0.MaterialCount(); ++i)
	{
		Corner2.GetMaterial(i).Source(Asset<Rendering::MaterialSource>::Load("dungeon/dungeon.mtl"));
	}
	Corner2.Transform.Position()(-2.5f, -0.75f, -2.5f);
	Corner2.Transform.Rotation() = Math::Quaternion::FromEuler(0, -2*Math::Constants::Pi<float>() / 2, 0);
	Corner2.QueueJobs();

	for (int i = 0; i < Corner0.MaterialCount(); ++i)
	{
		Corner3.GetMaterial(i).Source(Asset<Rendering::MaterialSource>::Load("dungeon/dungeon.mtl"));
	}
	Corner3.Transform.Position()(2.5f, -0.75f, -2.5f);
	Corner3.Transform.Rotation() = Math::Quaternion::FromEuler(0, -3 * Math::Constants::Pi<float>() / 2, 0);
	Corner3.QueueJobs();


}

void TestScene::Update(float dt)
{
	static float t = 0; t += dt;
	//OverheadLight.Transform.Position(cos(t) * 0.5f, 0.3f, sin(t) * 0.5f);
	OtherLight2.Transform.Position()(cos(t + Math::Constants::Pi<float>()/2) * 0.5f, 0.3f, sin(t + Math::Constants::Pi<float>()/2));
	OtherLight.Transform.Position()(cos(t - Math::Constants::Pi<float>() / 2), 0.3f, sin(t - Math::Constants::Pi<float>() / 2) * 0.5f);

	TestParticles.Transform().Position()(cos(t) * 0.5f, 3.0f, sin(t) * 0.5f);
	//TestParticles.Transform().CreateMatrix();
}

}