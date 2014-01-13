#include "RenderSystem.h"
#include "Drawable.h"
#include "DebugDraw.h"
#include <algorithm>

namespace Tocs {
namespace Rendering {

RenderSystem::RenderSystem(Graphics::GraphicsContext  &context)
	: QuadShader(Asset<Graphics::Shader>::Load("baseshaders/QuadTexturer.shd")),
	  FrameDepth (context.GetTarget().GetWidth(), context.GetTarget().GetHeight(), Graphics::DepthStencilFormat::D32S8),
	  FrameResult(context.GetTarget().GetWidth(), context.GetTarget().GetHeight(), Graphics::TextureFiltering::None, Graphics::TextureFormat::RGBA8),
	  Pipes(*this),
	  GContext(&context),
	  AlphaBuffer(*this),
	  GeometryBuffer(*this),
	  Shadows(*this)
{
	FrameTarget.SetTexture(FrameResult,0);
	FrameTarget.SetDepthBuffer(FrameDepth);
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

	//Pipes.DeferredPipe.Draw(cam);

	FrameTarget.Bind();

	//Render Deferred Lights
	//GeometryBuffer.DoLighting(*this);
	
	Context().ClearActiveBuffer();

	Pipes.OpaquePipe.Draw(cam);

	Pipes.WireframePipe.Draw(cam);

	Pipes.TransparentPipe.Draw(cam);
	
	AlphaBuffer.BlendAndPresent(*this);

	FrameTarget.UnBind();

	PushResult(Context());

	DebugDraw::Clear();
}

void RenderSystem::PushResult (Graphics::GraphicsContext &context)
{
	context.DisableDepthTest();
	context.DisableDepthWrite();
	QuadShader.Get().Bind ();
	QuadShader.Get()["Texture"] = FrameResult;
	RenderingQuad.PushGeometry(context);
	QuadShader.Get().UnBind();
	context.EnableDepthTest();
	context.EnableDepthWrite();
}

void RenderSystem::Update (float dt)
{	
	
}

void RenderSystem::Add(Light &light)
{
	Lights.push_back(&light);
}

void RenderSystem::Add(Drawable &drawable)
{
	Drawables.push_back(&drawable);
}


}}