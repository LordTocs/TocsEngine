#include "DeferredLightPipe.h"

namespace Tocs {
namespace Rendering {

DeferredLightPipe::DeferredLightPipe(const DeferredPipe &deferredpipe)
	: GBufferPipe (deferredpipe)
{

}

void DeferredLightPipe::BeginRendering (Graphics::GraphicsContext &context, const Camera &cam)
{
	context.DisableDepthTest();
	context.DisableDepthWrite ();
	context.EnableBackfaceCulling();
	context.AdditiveBlending();
}
void DeferredLightPipe::EndRendering   (Graphics::GraphicsContext &context, const Camera &cam)
{
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
	shader["ScreenWidth"] = cam.Width;
	shader["ScreenHeight"] = cam.Height;
	shader["CameraPosition"] = cam.Position;
	shader["InverseProjection"] = cam.GetInverseProjection();
	shader["InverseView"]       = Math::Matrix4::Inversion(cam.GetView());

	

}   

}}