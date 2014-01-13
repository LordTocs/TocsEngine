#include "DeferredPipe.h"
#include "RenderSystem.h"
namespace Tocs {
namespace Rendering {

DeferredPipe::DeferredPipe(RenderSystem &system)
: Pipe(system)
{
	
}

void DeferredPipe::BeginJob(Job &job, const Camera &camera)
{
	(*job.DrawShader)["View"] = camera.GetView();
	(*job.DrawShader)["Projection"] = camera.GetProjection();
}
void DeferredPipe::EndJob(Job &job, const Camera &camera)
{

}

void DeferredPipe::BeginDraw(const Camera &camera)
{
	System.GetGeometryBuffer().Bind();
}
void DeferredPipe::EndDraw(const Camera &camera)
{
	System.GetGeometryBuffer().UnBind();
}

}}