#include "DeferredPipe.h"
#include "RenderSystem.h"
using namespace Tocs;
using namespace Tocs::Graphics;

namespace Tocs {
namespace Rendering {

DeferredPipe::DeferredPipe(GraphicsContext &context, RenderSystem &system)
	: Buffer(context,system)
{ 

}

void DeferredPipe::BeginRendering (GraphicsContext &context,const Camera &camera)
{
	Buffer.Bind ();
	context.EnableBackfaceCulling();
	context.ClearActiveBuffer ();

}
void DeferredPipe::EndRendering (Graphics::GraphicsContext &context,const Camera &camera)
{
	Buffer.UnBind ();
	context.DisableBackfaceCulling();
}

void DeferredPipe::ApplyPipeInputs (Graphics::GraphicsContext &context, const Camera &cam, Graphics::Shader &shader)
{
}

}}