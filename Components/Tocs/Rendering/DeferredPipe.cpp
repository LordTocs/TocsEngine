#include "DeferredPipe.h"

using namespace Tocs;
using namespace Tocs::Graphics;

namespace Tocs {
namespace Rendering {

DeferredPipe::DeferredPipe(GraphicsContext &context)
	: Buffer(context)
{ 

}

void DeferredPipe::BeginRender (const Camera &camera, GraphicsContext &context)
{
	Buffer.Bind ();
	context.ClearActiveBuffer ();

}
void DeferredPipe::EndRender (const Camera &camera, Graphics::GraphicsContext &context)
{
	Buffer.UnBind ();
}

}}