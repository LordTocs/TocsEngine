#include "TestScene.h"
#include <Tocs/Math/Constants.h>

namespace Tocs {

TestScene::TestScene(Rendering::RenderSystem &system)
: Table(system, Asset<Rendering::Mesh>::Load("table/table.3ds"))

, Sword(system, Asset<Rendering::Mesh>::Load("sword/sword.obj"))
, Apple(system, Asset<Rendering::Mesh>::Load("apple/apple.3ds"))
, Vial(system, Asset<Rendering::Mesh>::Load("vial/vial.3ds"))
, Flask(system, Asset<Rendering::Mesh>::Load("vial/flask.3ds"))
, Book(system,  Asset<Rendering::Mesh>::Load("book/book.3ds"))
, OpenScroll(system, Asset<Rendering::Mesh>::Load("scrolls/OpenScroll.3ds"))
, Candle(system, Asset<Rendering::Mesh>::Load("candle/candle.3ds"))
, CandleHolder(system, Asset<Rendering::Mesh>::Load("candle/holder.3ds"))
, Crystal(system, Asset<Rendering::Mesh>::Load("crystal/crystal.3ds"))
//, TableLight(system, Math::Vector3(0, 0.3, 0), 10, Math::Color(214,0,0))
//, OverheadLight(system, Math::Vector3(0, 2.4f, 0), 10, Math::Color(250, 237, 155))
, OtherLight(system, Math::Vector3(0, 0.3, 0.5), 10, Math::Color(250, 237, 155))
//, OtherLight2(system, Math::Vector3(0, 0.3, -0.5), 10, Math::Color(250, 237, 155))
, CandleLight(system, Math::Vector3(0.5f, 0.38f, -0.25f), 4, Math::Color(250, 237, 155))
//, TestParticles(system, Asset<Rendering::ParticleSystemSource>::Load("particles/test.particle"))
{
	//OtherLight.Intensity = 1.0f;
	//OtherLight2.Intensity = 0.1f;
	//OverheadLight.Intensity = 0.1f;

	Table.GetMaterial(0).Source(Asset <Rendering::MaterialSource>::Load("table/table.mtl"));
	Table.Transform.Scale(0.75f, 0.75f, 0.75f);
	//Table.Transform.Position(0, -2.77/2, 0);
	Table.Transform.CreateMatrix();
	Table.QueueJobs();

	Sword.GetMaterial(0).Source(Asset<Rendering::MaterialSource>::Load("sword/sword.mtl"));
	Sword.Transform.Scale(0.5f, 0.5f, 0.5f);
	Sword.Transform.Rotation = Math::Quaternion::FromEuler(Math::Constants::Pi<float>() / 2,0 * Math::Constants::Pi<float>() / 4, 0);
	Sword.Transform.Position(-0.8f, 0.075f, 0);
	Sword.Transform.CreateMatrix();
	Sword.QueueJobs();

	OpenScroll.GetMaterial(0).Source(Asset<Rendering::MaterialSource>::Load("scrolls/scroll.mtl"));
	OpenScroll.Transform.Scale(0.5f, 0.5f, 0.5f);
	OpenScroll.Transform.Position(0.5f, 0.025f, 0.0f);
	OpenScroll.Transform.CreateMatrix();
	OpenScroll.QueueJobs();

	Candle.GetMaterial(0).Source(Asset<Rendering::MaterialSource>::Load("candle/candle.mtl"));
	Candle.Transform.Scale(1.0f, 1.0f, 1.0f);
	Candle.Transform.Position(0.5f, 0.02f, -0.25f);
	Candle.Transform.Rotation = Math::Quaternion::FromEuler(0,-Math::Constants::Pi<float>()/2, 0);
	Candle.Transform.CreateMatrix();
	Candle.QueueJobs();

	CandleHolder.GetMaterial(0).Source(Asset<Rendering::MaterialSource>::Load("candle/holder.mtl"));
	CandleHolder.Transform.Scale(1.0f, 1.0f, 1.0f);
	CandleHolder.Transform.Position(0.5f, 0.02f, -0.25f);
	CandleHolder.Transform.CreateMatrix();
	CandleHolder.QueueJobs();

	Apple.GetMaterial(0).Source(Asset <Rendering::MaterialSource>::Load("apple/apple.mtl"));
	Apple.Transform.Position(1, 0.1f, 0);
	Apple.Transform.CreateMatrix();
	Apple.QueueJobs();

	Vial.GetMaterial(0).Source(Asset <Rendering::MaterialSource>::Load("vial/vial.mtl"));
	Vial.Transform.Position(0.5f, 0.14f, 0.5f);
	Vial.Transform.CreateMatrix();
	Vial.QueueJobs();

	Flask.GetMaterial(0).Source(Asset <Rendering::MaterialSource>::Load("vial/vial.mtl"));
	Flask.Transform.Position(0.5f, 0.13f, -0.5f);
	Flask.Transform.CreateMatrix();
	Flask.QueueJobs();

	Crystal.GetMaterial(0).Source(Asset <Rendering::MaterialSource>::Load("crystal/rock.mtl"));
	Crystal.GetMaterial(1).Source(Asset <Rendering::MaterialSource>::Load("crystal/crystal.mtl"));
	Crystal.Transform.Position(/*0.5f*/0, 0.2f, 0);
	Crystal.Transform.CreateMatrix();
	Crystal.QueueJobs();

	//
	Book.GetMaterial(0).Source(Asset <Rendering::MaterialSource>::Load("book/book_red.mtl"));
	Book.Transform.Position(-0.5f, 0.08f, 0.5f);
	Book.Transform.Scale(1.3f, 1.3f, 1.3f);
	Book.Transform.CreateMatrix();
	Book.QueueJobs();


}

void TestScene::Update(float dt)
{
	static float t = 0; t += dt;
	//OverheadLight.Transform.Position(cos(t) * 0.5f, 0.3f, sin(t) * 0.5f);
	//OtherLight2.Transform.Position(cos(t + Math::Constants::Pi<float>()/2) * 0.5f, 0.3f, sin(t + Math::Constants::Pi<float>()/2));
	OtherLight.Transform.Position(cos(t - Math::Constants::Pi<float>() / 2), 0.3f, sin(t - Math::Constants::Pi<float>() / 2) * 0.5f);
}

}