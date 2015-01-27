#include "DeferredPipe.h"
#include "RenderSystem.h"
namespace Tocs {
namespace Rendering {

DeferredPipe::DeferredPipe(RenderSystem &system)
: Pipe(system)
{
	
}

void DeferredPipe::BeginDraw(const Camera &camera)
{
	System.GetGeometryBuffer().Bind();
	System.Context().ClearActiveBuffer();
}
void DeferredPipe::EndDraw(const Camera &camera)
{
	System.GetGeometryBuffer().UnBind();
}

}}