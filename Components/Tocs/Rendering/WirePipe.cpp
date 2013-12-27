#include "WirePipe.h"
#include "RenderSystem.h"
#include "DebugDraw.h"
namespace Tocs {
namespace Rendering {

void WirePipe::JobAdded(Job &job)
{

}

void WirePipe::BeginJob(Job &job, const Camera &camera)
{
	(*job.DrawShader)["View"] = camera.GetView();
	(*job.DrawShader)["Projection"] = camera.GetProjection();
}

void WirePipe::EndJob(Job &job, const Camera &camera)
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