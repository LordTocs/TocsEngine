#include "DeferredPipe.h"

using namespace Tocs;
using namespace Tocs::Graphics;

namespace Tocs {
namespace Rendering {

DeferredPipe::DeferredPipe(GraphicsContext &context)
	: Buffer(context)
{ 

}

void DeferredPipe::BeginRendering (GraphicsContext &context,const Camera &camera)
{
	Buffer.Bind ();
	context.ClearActiveBuffer ();

}
void DeferredPipe::EndRendering (Graphics::GraphicsContext &context,const Camera &camera)
{
	Buffer.UnBind ();
}

void DeferredPipe::ApplyPipeInputs (Graphics::GraphicsContext &context, const Camera &cam, Graphics::Shader &shader)
{

}

}}