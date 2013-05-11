#include "NonLitPipe.h"

namespace Tocs {
namespace Rendering {

void NonLitPipe::BeginRendering (Graphics::GraphicsContext &context, const Camera &cam)
{
	context.EnableDepthTest();
	context.EnableDepthWrite();
}
void NonLitPipe::EndRendering   (Graphics::GraphicsContext &context, const Camera &cam)
{

}
void NonLitPipe::ApplyPipeInputs (Graphics::GraphicsContext &context, const Camera &cam, Graphics::Shader &shader)
{

}

}}
