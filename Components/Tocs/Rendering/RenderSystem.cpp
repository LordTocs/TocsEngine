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
	  GContext(&context)
{
	FrameTarget.SetTexture(FrameResult,0);
	FrameTarget.SetDepthBuffer(FrameDepth);
}

void RenderSystem::Render (const Camera &cam)
{
	//Pipes.DeferredPipe.Render (context,cam);
	//Pipes.DeferredLightPipe.Render (context,cam);

	Context().ClearActiveBuffer();

	LightTiles.Configure(cam, Lights);

	Pipes.OpaquePipe.Draw(cam);

	Pipes.WireframePipe.Draw(cam);
	

	//PushResult (context);

	DebugDraw::Clear();
}

void RenderSystem::PushResult (Graphics::GraphicsContext &context)
{
	/*context.DisableDepthTest();
	context.DisableDepthWrite();
	QuadShader.Get().Bind ();
	QuadShader.Get()["Texture"] = FrameResult;
	RenderingQuad.PushGeometry(context);
	QuadShader.Get().UnBind();
	context.EnableDepthTest();
	context.EnableDepthWrite();*/
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