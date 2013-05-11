#include "WirePipe.h"


namespace Tocs {
namespace Rendering {

void WirePipe::BeginRendering (Graphics::GraphicsContext &context, const Camera &cam)
{
	context.EnableDepthTest();
	context.EnableDepthWrite();
	context.EnableWireframe();
}
void WirePipe::EndRendering   (Graphics::GraphicsContext &context, const Camera &cam)
{
	context.DisableWireframe();
}
void WirePipe::ApplyPipeInputs (Graphics::GraphicsContext &context, const Camera &cam, Graphics::Shader &shader)
{
}

}}
