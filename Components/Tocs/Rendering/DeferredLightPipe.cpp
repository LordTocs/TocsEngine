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
}
void DeferredLightPipe::EndRendering   (Graphics::GraphicsContext &context, const Camera &cam)
{
	context.EnableDepthTest ();
	context.EnableDepthWrite ();
}

void DeferredLightPipe::ApplyPipeInputs (Graphics::GraphicsContext &context, const Camera &cam, Graphics::Shader &shader)
{
	shader["ColorBuffer"] = GBufferPipe.GetBuffer().GetAlbedo();
	shader["NormalBuffer"] = GBufferPipe.GetBuffer().GetNormals();
	shader["SpecularBuffer"] = GBufferPipe.GetBuffer().GetSpecular();
	shader["DepthBuffer"] = GBufferPipe.GetBuffer ().GetLinearDepth();
}

}}