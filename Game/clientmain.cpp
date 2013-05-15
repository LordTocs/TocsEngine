#include <iostream>
#include <utility>
#include <Tocs/Rendering/Init.h>
#include "Game.h"

using namespace Tocs;
using namespace std;
/*
int main ()
{
	int pause;
	SimpleWindow window ("Game",500,500,false,false);
	GraphicsContext context (window);
	//context.SetClearColor (Color (100,149,237));
	context.SetClearDepth(1000);
	context.EnableDepthTest();
	RenderInitList ().Init ();

	//Asset<Material> crate = Asset<Material>::Load ("Crate.mtl");
	//Asset<Texture2D> cratetex = Asset<Texture2D>::Load("Crate.jpg");
	//Asset<MaterialTemplate> unlittemplate = Asset<MaterialTemplate>::Load("UnlitTemplate.tgl");
	//MaterialShading testshading (unlittemplate);
	//testshading["Albedo"].Map(cratetex);

	//StaticGeometryType ptngeom;
	//ptngeom.ImportShader (Asset<ShaderCode>::Load ("PositionTextureNormal.vert"));

	//StaticGeometry testgeom (Primitives::Cube.Get(), ptngeom);
	//testgeom["World"].Value(Matrix4::Identity);

	//Job testjob (testgeom,testshading);
	

	//NonLitPipe testpipe;
	//testpipe.AppendJob(testjob);
	

	//Asset<MaterialTemplate> deftemplate = Asset<MaterialTemplate>::Load("DeferredTemplate.tgl");
	//MaterialShading testdefshading (deftemplate);
	//testdefshading["Albedo"].Map(cratetex);
	//testdefshading["Specular"].Map(cratetex);
	//testdefshading["Roughness"].Value(0.5f);
	//testdefshading["SpecularPower"].Value(0.5f);
	//testdefshading["SpecularIntensity"].Value(0.5f);

	//<%vec3 Albedo%>
	//<%vec3 Specular%>
	//<%float Roughness%>
	//<%float SpecularPower%>
	//<%float SpecularIntensity%>

	//Job testdefjob (testgeom,testdefshading);
	
	//DeferredPipe testdefpipe (context);
	//testdefpipe.AppendJob(testdefjob);


	RenderSystem rendersystem (context);
	Model cubemodel (Asset<Mesh>::Wrap(Primitives::Cube.Get()),rendersystem);
	cubemodel.Materials[0].SetMaterial(Asset<Material>::Load("Crate.mtl"));

	cubemodel.Show();
	cubemodel.Transform.Scale.Y = 2;
	cubemodel.Transform.CreateMatrix();

	PointLight light (rendersystem);
	light.Show();
	light.Radius = 10;
	light.Transform.Position (4,4,4);
	light.Transform.CreateMatrix();

	PointLight light2 (rendersystem);
	light2.Show();
	light2.Radius = 10;
	light2.Color = Math::Color(255,100,100);
	light2.Transform.Position (-4,4,-4);
	light2.Transform.CreateMatrix();
	
	Camera cam (500,500);
	OrbitCameraController camcontroller(cam);
	cam.Compute ();

	Ticker ticker;
	float t = 0;
	while (!window.IsExiting ())
	{
		window.PumpMessages ();
		context.ClearActiveBuffer ();
		float dt = ticker.GetTickTime();
		t += dt;

		light.Transform.Position(0,sin(t)*5,cos(t)*5);
		light2.Transform.Position(cos(t)*5,0,sin(t)*5);


		window.Input.Update(dt);

		if (window.Input.Keyboard.IsPressed(0x25))
		{
			//left
			camcontroller.DoYaw(dt);
		}
		else if (window.Input.Keyboard.IsPressed(0x27))
		{
			//right
			camcontroller.DoYaw (-dt);
		}
		else if (window.Input.Keyboard.IsPressed(0x26))
		{
			//up
			camcontroller.DoPitch(dt);
		}
		else if (window.Input.Keyboard.IsPressed(0x28))
		{
			//down
			camcontroller.DoPitch(-dt);
		}
		else if (window.Input.Keyboard.IsPressed(0x6B))
		{
			//zoomin
			camcontroller.DoZoom(-dt * 5);
		}
		else if (window.Input.Keyboard.IsPressed(0x6D))
		{
			//down
			camcontroller.DoZoom(dt * 5);
		}

		camcontroller.Calculate();
		cam.Compute ();
		rendersystem.Update(dt);
		rendersystem.Render(context,cam);

		context.FlipToScreen ();
	}

	window.Close ();

	int p;
	cin >> p;

	return 0;
}*/

int main ()
{
	Game game;
	game.Start();
}