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
#include <Tocs/Rendering/Camera.h>
#include <Tocs/Rendering/Init.h>
#include <Tocs/Rendering/Primitives.h>
#include <Tocs/Rendering/MaterialValue.h>
#include <Tocs/Rendering/NonLitPipe.h>
#include <Tocs/Rendering/Job.h>
#include <Tocs/Rendering/StaticGeometry.h>
#include <Tocs/Rendering/MaterialShading.h>
#include <Tocs/Rendering/DeferredPipe.h>

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
	context.SetClearDepth(1000);
	context.EnableDepthBuffering();
	RenderInitList ().Init ();
	
	//Asset<Material> crate = Asset<Material>::Load ("Crate.mtl");
	Asset<Texture2D> cratetex = Asset<Texture2D>::Load("Crate.jpg");
	Asset<MaterialTemplate> unlittemplate = Asset<MaterialTemplate>::Load("UnlitTemplate.tgl");
	MaterialShading testshading (unlittemplate);
	testshading["Albedo"].Map(cratetex);

	StaticGeometryType ptngeom;
	ptngeom.ImportShader (Asset<ShaderCode>::Load ("PositionTextureNormal.vert"));

	StaticGeometry testgeom (Primitives::Cube.Get(), ptngeom);
	testgeom["World"].Value(Matrix4::Identity);

	Job testjob (testgeom,testshading);
	

	NonLitPipe testpipe;
	testpipe.AppendJob(testjob);
	

	Asset<MaterialTemplate> deftemplate = Asset<MaterialTemplate>::Load("DeferredTemplate.tgl");
	MaterialShading testdefshading (deftemplate);
	testdefshading["Albedo"].Map(cratetex);
	testdefshading["Specular"].Map(cratetex);
	testdefshading["Roughness"].Value(0.5f);
	testdefshading["SpecularPower"].Value(0.5f);
	testdefshading["SpecularIntensity"].Value(0.5f);

	//<%vec3 Albedo%>
	//<%vec3 Specular%>
	//<%float Roughness%>
	//<%float SpecularPower%>
	//<%float SpecularIntensity%>

	Job testdefjob (testgeom,testdefshading);
	
	DeferredPipe testdefpipe (context);
	testdefpipe.AppendJob(testdefjob);


	Camera cam (1);

	cam.Position(1.5,1.5,1.5);
	cam.LookAt(0,0,0);
	cam.Compute ();

	//Asset<Shader> testshader = Asset<Shader>::Load ("Solid.shd");
	
	//testshader.Get().PrintDebugInformation ();


	while (!window.IsExiting ())
	{
		window.PumpMessages ();
		context.ClearActiveBuffer ();
		cam.Compute ();
		

		testpipe.Render (context,cam);
		testdefpipe.Render (context,cam);
		/*testshader->Bind ();
		cam.PassToShader (testshader.Get ());
		testshader.Get()["World"] = Math::Matrix4::CreateScale (0.5,0.5,0.5);
		Primitives::Cube.Get().Bind ();
		Primitives::Cube.Get().PushPartGeometry (0);
		Primitives::Cube.Get().UnBind ();
		testshader->UnBind ();*/

		context.FlipToScreen ();
	}

	window.Close ();

	int p;
	cin >> p;

	return 0;
}

