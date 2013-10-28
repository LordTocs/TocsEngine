#include "RenderSystem.h"
#include <algorithm>

namespace Tocs {
namespace Rendering {

RenderSystem::RenderSystem(Graphics::GraphicsContext  &context)
	: /*Pipes(context,*this),*/
	  QuadShader(Asset<Graphics::Shader>::Load("baseshaders/QuadTexturer.shd")),
	  FrameDepth (context.GetTarget().GetWidth(), context.GetTarget().GetHeight(), Graphics::DepthStencilFormat::D32S8),
	  FrameResult(context.GetTarget().GetWidth(), context.GetTarget().GetHeight(), Graphics::TextureFiltering::None, Graphics::TextureFormat::RGBA8)
{
	FrameTarget.SetTexture(FrameResult,0);
	FrameTarget.SetDepthBuffer(FrameDepth);
}

void RenderSystem::Render (Graphics::GraphicsContext &context,const Camera &cam)
{
	//FrameTarget.Bind();
	//context.ClearActiveBuffer();
	//FrameTarget.UnBind();
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
	//Pipes.UnlitPipe.Render (context,cam);
	//Pipes.WireframePipe.Render (context,cam);
	//FrameTarget.UnBind();

	

	PushResult (context);
}

void RenderSystem::PushResult (Graphics::GraphicsContext &context)
{
	//context.DisableDepthTest();
	//context.DisableDepthWrite();
	//QuadShader.Get().Bind ();
	//QuadShader.Get()["Texture"] = FrameResult;
	//RenderingQuad.PushGeometry();
	//QuadShader.Get().UnBind();
	//context.EnableDepthTest();
	//context.EnableDepthWrite();
}

void RenderSystem::Update (float dt)
{	
	
}


}}