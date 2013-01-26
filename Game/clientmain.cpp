#include <iostream>
#include <utility>
#include <Tocs/Net/Socket.h>
#include <Tocs/Core/BinaryManipulator.h>
#include <Tocs/Core/Tokenizer.h>
#include <Tocs/Graphics/SimpleWindow.h>
#include <Tocs/Graphics/GraphicsContext.h>
#include <Tocs/Rendering/ShaderPermutator.h>
#include <Tocs/Rendering/PermutationValueSet.h>
#include <Tocs/Rendering/Material.h>
#include <Tocs/Rendering/MeshBuilder.h>
#include <Tocs/Rendering/Vertices.h>
#include <Tocs/Rendering/Model.h>

using namespace Tocs;
using namespace Tocs::Lexing;
using namespace Tocs::Net;
using namespace Tocs::Graphics;
using namespace Tocs::Math;
using namespace Tocs::Rendering;
using namespace Tocs::Rendering::Permutations;
using namespace Tocs::Rendering::Building;
using namespace std;




int main ()
{
	int pause;
	SimpleWindow window ("Game",500,500,false,false);
	GraphicsContext context (window);
	context.SetClearColor (Color (100,149,237));
	
	Asset<Material> testmat = Asset<Material>::Load ("TestMat.mtl");


	MeshBuilder <PositionTextureNormal>  Builder;

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

	Builder.CreateQuad (v000,v010,v110,v100);
	Builder.CreateQuad (v111,v011,v001,v101);
	Builder.CreateQuad (v010,v011,v111,v110);
	Builder.CreateQuad (v000,v100,v101,v001);
	Builder.CreateQuad (v001,v111,v101,v100);
	Builder.CreateQuad (v010,v000,v001,v011);

	RenderSystem Renderer;

	Mesh cubemesh (Builder.CreateMesh ());

	Model cubemodel (cubemesh);

	Renderer.AddObject (cubemodel);

	


	while (!window.IsExiting ())
	{
		window.PumpMessages ();
		context.ClearActiveBuffer ();

		Renderer.Render (context);

		context.FlipToScreen ();
	}

	window.Close ();

	int p;
	cin >> p;

	return 0;
}

