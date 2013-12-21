#include "RenderSystem.h"
#include "Drawable.h"
#include <algorithm>

namespace Tocs {
namespace Rendering {

RenderSystem::RenderSystem(Graphics::GraphicsContext  &context)
	: QuadShader(Asset<Graphics::Shader>::Load("baseshaders/QuadTexturer.shd")),
	  FrameDepth (context.GetTarget().GetWidth(), context.GetTarget().GetHeight(), Graphics::DepthStencilFormat::D32S8),
	  FrameResult(context.GetTarget().GetWidth(), context.GetTarget().GetHeight(), Graphics::TextureFiltering::None, Graphics::TextureFormat::RGBA8),
	  Pipes(context,*this)
{
	FrameTarget.SetTexture(FrameResult,0);
	FrameTarget.SetDepthBuffer(FrameDepth);
}

void RenderSystem::Render (Graphics::GraphicsContext &context,const Camera &cam)
{
	//Pipes.DeferredPipe.Render (context,cam);
	//Pipes.DeferredLightPipe.Render (context,cam);
	//
	////foreach light
	////render forward pipe
	//
	//
	////foreach light
	////render translucent pipe
	//
	//
	//
	//FrameTarget.Bind();
	

	context.ClearActiveBuffer();

	Pipes.ForwardPipe.Draw(*this, context, cam);

	//FrameTarget.UnBind();
	Pipes.WireframePipe.Draw(*this, context, cam);
	

	//PushResult (context);
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