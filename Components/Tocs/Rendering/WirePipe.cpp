#include "WirePipe.h"
#include "RenderSystem.h"
#include "DebugDraw.h"
namespace Tocs {
namespace Rendering {

void WirePipe::JobAdded(Job &job)
{

}

void WirePipe::BeginDraw(const Camera &camera)
{
	DebugDraw::Draw(System.Context(), camera);
	System.Context().EnableWireframe();
	
}

void WirePipe::EndDraw(const Camera &camera)
{
	System.Context().DisableWireframe();
}

}}