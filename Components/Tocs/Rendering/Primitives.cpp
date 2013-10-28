#include "Primitives.h"
//#include "Init.h"
//#include "MeshBuilder.h"
#include "Vertices.h"
/*
using namespace Tocs::Math;

namespace Tocs {
namespace Rendering {

Mesh Primitives::BuildCube ()
{
	Building::MeshBuilder<PositionTextureNormal> CubeBuilder;
 
    auto a010 = CubeBuilder.GetVertex();

    auto a110 = CubeBuilder.GetVertex();

    auto a100 = CubeBuilder.GetVertex();

    auto a000 = CubeBuilder.GetVertex();

    

    a010.Get()(Vector3(-0.5, 0.5,-0.5),Vector2(0,0));

    a110.Get()(Vector3( 0.5, 0.5,-0.5),Vector2(1,0));

    a100.Get()(Vector3( 0.5,-0.5,-0.5),Vector2(1,1));

    a000.Get()(Vector3(-0.5,-0.5,-0.5),Vector2(0,1));

    

    CubeBuilder.CreateQuad(a010,a110,a100,a000);

    

    auto b011 = CubeBuilder.GetVertex();

    auto b111 = CubeBuilder.GetVertex();

    auto b010 = CubeBuilder.GetVertex();

    auto b110 = CubeBuilder.GetVertex();

    

    b011.Get()(Vector3(-0.5, 0.5, 0.5),Vector2(0,0));

    b111.Get()(Vector3( 0.5, 0.5, 0.5),Vector2(1,0));

    b110.Get()(Vector3( 0.5, 0.5,-0.5),Vector2(1,1));

    b010.Get()(Vector3(-0.5, 0.5,-0.5),Vector2(0,1));

    

    CubeBuilder.CreateQuad(b011,b111,b110,b010);


    auto c111 = CubeBuilder.GetVertex();

    auto c011 = CubeBuilder.GetVertex();

    auto c001 = CubeBuilder.GetVertex();

    auto c101 = CubeBuilder.GetVertex();

    

    c111.Get()(Vector3( 0.5, 0.5, 0.5),Vector2(0,0));

    c011.Get()(Vector3( 0.5,-0.5, 0.5),Vector2(1,0));

    c001.Get()(Vector3(-0.5,-0.5, 0.5),Vector2(1,1));

    c101.Get()(Vector3(-0.5, 0.5, 0.5),Vector2(0,1));

    

    CubeBuilder.CreateQuad(c101,c001,c011,c111);

    

    auto d101 = CubeBuilder.GetVertex();

    auto d001 = CubeBuilder.GetVertex();

    auto d000 = CubeBuilder.GetVertex();

    auto d100 = CubeBuilder.GetVertex();

    

    d101.Get()(Vector3( 0.5,-0.5, 0.5),Vector2(0,0));

    d001.Get()(Vector3(-0.5,-0.5, 0.5),Vector2(1,0));

    d000.Get()(Vector3(-0.5,-0.5,-0.5),Vector2(1,1));

    d100.Get()(Vector3( 0.5,-0.5,-0.5),Vector2(0,1));

    

    CubeBuilder.CreateQuad(d101,d001,d000,d100);

    

    auto e011 = CubeBuilder.GetVertex();

    auto e010 = CubeBuilder.GetVertex();

    auto e000 = CubeBuilder.GetVertex();

    auto e001 = CubeBuilder.GetVertex();

    

    e011.Get()(Vector3(-0.5, 0.5, 0.5),Vector2(0,0));

    e010.Get()(Vector3(-0.5, 0.5,-0.5),Vector2(1,0));

    e000.Get()(Vector3(-0.5,-0.5,-0.5),Vector2(1,1));

    e001.Get()(Vector3(-0.5,-0.5, 0.5),Vector2(0,1));

    

    CubeBuilder.CreateQuad(e011,e010,e000,e001);

    

    auto f110 = CubeBuilder.GetVertex();

    auto f111 = CubeBuilder.GetVertex();

    auto f101 = CubeBuilder.GetVertex();

    auto f100 = CubeBuilder.GetVertex();

    

    f110.Get()(Vector3( 0.5, 0.5,-0.5),Vector2(0,0));

    f111.Get()(Vector3( 0.5, 0.5, 0.5),Vector2(1,0));

    f101.Get()(Vector3( 0.5,-0.5, 0.5),Vector2(1,1));

    f100.Get()(Vector3( 0.5,-0.5,-0.5),Vector2(0,1));

    

    CubeBuilder.CreateQuad(f110,f111,f101,f100);

	CubeBuilder.ComputeNormals ();

	return CubeBuilder.CreateMesh ();
}

FirstUseStatic<Mesh,&Primitives::BuildCube> Primitives::Cube;


}}*/