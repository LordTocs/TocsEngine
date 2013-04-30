#include "LightHulls.h"
#include "Init.h"
#include <Tocs/Core/StaticInitializer.h>
#include "MeshBuilder.h"
#include "Vertices.h"
namespace Tocs {
namespace Rendering {

static Mesh BuildCube ()
{
	Tocs::Rendering::Building::MeshBuilder <PositionOnly> Builder;

	auto v000 = Builder.GetVertex ();
	v000.Get ().Position (-1,-1,-1);
	auto v001 = Builder.GetVertex ();
	v001.Get ().Position (-1,-1, 1);
	auto v010 = Builder.GetVertex ();
	v010.Get ().Position (-1, 1,-1);
	auto v011 = Builder.GetVertex ();
	v011.Get ().Position (-1, 1, 1);
	auto v100 = Builder.GetVertex ();
	v100.Get ().Position ( 1,-1,-1);
	auto v101 = Builder.GetVertex ();
	v101.Get ().Position ( 1,-1, 1);
	auto v110 = Builder.GetVertex ();
	v110.Get ().Position ( 1, 1,-1);
	auto v111 = Builder.GetVertex ();
	v111.Get ().Position ( 1, 1, 1);

	auto f1 = Builder.CreateQuad (v000,v010,v110,v100);
	auto f2 = Builder.CreateQuad (v111,v011,v001,v101);
	auto f3 = Builder.CreateQuad (v010,v011,v111,v110);
	auto f4 = Builder.CreateQuad (v000,v100,v101,v001);
	auto f5 = Builder.CreateQuad (v001,v111,v101,v100);
	auto f6 = Builder.CreateQuad (v010,v000,v001,v011);

	return Builder.CreateMesh ();
}
LateStatic <Mesh> LightHulls::Cube (BuildCube,RenderInitList ());

static Mesh BuildInverseCube ()
{
	Building::MeshBuilder <PositionOnly> Builder;

	auto v000 = Builder.GetVertex ();
	v000.Get ().Position (-1,-1,-1);
	auto v001 = Builder.GetVertex ();
	v001.Get ().Position (-1,-1, 1);
	auto v010 = Builder.GetVertex ();
	v010.Get ().Position (-1, 1,-1);
	auto v011 = Builder.GetVertex ();
	v011.Get ().Position (-1, 1, 1);
	auto v100 = Builder.GetVertex ();
	v100.Get ().Position ( 1,-1,-1);
	auto v101 = Builder.GetVertex ();
	v101.Get ().Position ( 1,-1, 1);
	auto v110 = Builder.GetVertex ();
	v110.Get ().Position ( 1, 1,-1);
	auto v111 = Builder.GetVertex ();
	v111.Get ().Position ( 1, 1, 1);

	auto f1 = Builder.CreateQuad (v000,v010,v110,v100);
	auto f2 = Builder.CreateQuad (v111,v011,v001,v101);
	auto f3 = Builder.CreateQuad (v010,v011,v111,v110);
	auto f4 = Builder.CreateQuad (v000,v100,v101,v001);
	auto f5 = Builder.CreateQuad (v001,v111,v101,v100);
	auto f6 = Builder.CreateQuad (v010,v000,v001,v011);

	f1.first.FlipOrder ();
	f1.second.FlipOrder ();
	
	f2.first.FlipOrder ();
	f2.second.FlipOrder ();
	
	f3.first.FlipOrder ();
	f3.second.FlipOrder ();
	
	f4.first.FlipOrder ();
	f4.second.FlipOrder ();
	
	f5.first.FlipOrder ();
	f5.second.FlipOrder ();

	f6.first.FlipOrder ();
	f6.second.FlipOrder ();

	return Builder.CreateMesh ();
}

LateStatic <Mesh> LightHulls::InverseCube (BuildInverseCube, RenderInitList ());

static StaticGeometryType CreateGeometryType ()
{
	StaticGeometryType result;

	result.ImportShader (Asset<Graphics::ShaderCode>::Load ("PointLight.vert"));

	return std::move(result);
}

LateStatic <StaticGeometryType> LightHulls::GeometryType (CreateGeometryType, RenderInitList ());


}}