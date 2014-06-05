#include "RenderSystem.h"
#include "Drawable.h"
#include "DebugDraw.h"
#include <algorithm>

namespace Tocs {
namespace Rendering {

RenderSystem::RenderSystem(Graphics::GraphicsContext  &context)
	: QuadShader(Asset<Graphics::Shader>::Load("shaders/QuadTexturer.shd")),
	  FrameDepth (context.GetTarget().GetWidth(), context.GetTarget().GetHeight(), Graphics::DepthStencilFormat::D32S8),
	  Pipes(*this),
	  GContext(&context),
	  AlphaBuffer(*this),
	  GeometryBuffer(*this),
	  Shadows(*this),
	  PostProcesses(*this)
{
}

void RenderSystem::Render (const Camera &cam)
{
	for (auto &l : Lights)
	{
		l->ComputeScreenRect(cam);
	}

	Shadows.AssignShadowMaps(*this);

	LightTiles.Configure(cam, Lights);

	cam.SetUpViewport(Context());

	AlphaBuffer.Clear(*this);

	Pipes.DeferredPipe.Draw(cam);

	PostProcesses.GetCurrentFrameTarget().Bind();
	
	Context().SetClearColor(Math::Color(128,128,128));
	Context().ClearActiveBuffer();

	Pipes.OpaquePipe.Draw(cam);

	Pipes.WireframePipe.Draw(cam); 

	Pipes.TransparentPipe.Draw(cam);
	
	AlphaBuffer.BlendAndPresent(*this);

	PostProcesses.GetCurrentFrameTarget().UnBind();

	//Renderglow
	Pipes.GlowPipe.Draw(cam);

	cam.SetUpViewport(Context());

	PostProcesses.Apply();

	PushResult(Context());

	DebugDraw::Clear();
}

void RenderSystem::PushResult (Graphics::GraphicsContext &context)
{
	context.DisableDepthTest();
	context.DisableDepthWrite();
	QuadShader.Get().Bind ();
	QuadShader.Get()["Texture"] = PostProcesses.GetCurrentFrameResult();
	RenderingQuad.PushGeometry(context);
	QuadShader.Get().UnBind();
	context.EnableDepthTest();
	context.EnableDepthWrite();
}

void RenderSystem::Update (float dt)
{	
	for (auto &d : Drawables)
	{
		d->Update(dt);
	}
	Context().VertexArrayMemoryBarrier();
}

void RenderSystem::Add(Light &light)
{
	Lights.push_back(&light);
}

void RenderSystem::Add(Drawable &drawable)
{
	Drawables.push_back(&drawable);
}

void RenderSystem::Remove(const Light &light)
{
	auto i = std::find(Lights.begin(), Lights.end(), &light);
	if (i == Lights.end())
		return;

	Lights.erase(i);
}

void RenderSystem::Remove(const Drawable &drawable)
{
	auto i = std::find(Drawables.begin(), Drawables.end(), &drawable);
	if (i == Drawables.end())
		return;

	Drawables.erase(i);
}


}}