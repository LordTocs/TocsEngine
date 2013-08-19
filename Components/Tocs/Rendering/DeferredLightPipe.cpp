#include "DeferredLightPipe.h"
#include "RenderSystem.h"
namespace Tocs {
namespace Rendering {

DeferredLightPipe::DeferredLightPipe(Graphics::GraphicsContext &context, RenderSystem &system)
	: GBufferPipe (system.Pipes.DeferredPipe),
	  ResultTarget (system.FrameTarget)
{
}


void DeferredLightPipe::BeginRendering (Graphics::GraphicsContext &context, const Camera &cam)
{
	context.DisableDepthTest();
	context.DisableDepthWrite ();
	context.EnableBackfaceCulling();
	context.AdditiveBlending();
	ResultTarget.Bind();
	context.ClearColor();
}
void DeferredLightPipe::EndRendering   (Graphics::GraphicsContext &context, const Camera &cam)
{
	ResultTarget.UnBind();
	context.EnableDepthTest ();
	context.EnableDepthWrite ();
	context.DisableBackfaceCulling();
	context.NormalBlending();
}

void DeferredLightPipe::ApplyPipeInputs (Graphics::GraphicsContext &context, const Camera &cam, Graphics::Shader &shader)
{
	shader["ColorBuffer"] = GBufferPipe.GetBuffer().GetAlbedo();
	shader["NormalBuffer"] = GBufferPipe.GetBuffer().GetNormals();
	shader["SpecularBuffer"] = GBufferPipe.GetBuffer().GetSpecular();
	shader["DepthBuffer"] = GBufferPipe.GetBuffer ().GetLinearDepth();
	shader["InverseScreenWidth"] = 1.0f / cam.Width;
	shader["InverseScreenHeight"] = 1.0f / cam.Height;
	shader["InverseProjection"] = cam.GetInverseProjection();
}   

}}