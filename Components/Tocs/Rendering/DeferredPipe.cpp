#include "DeferredPipe.h"
#include "RenderSystem.h"
namespace Tocs {
namespace Rendering {

DeferredPipe::DeferredPipe(RenderSystem &system)
: Pipe(system), GeometryBuffer(system.Context(),system)
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
	GeometryBuffer.Bind();
}
void DeferredPipe::EndDraw(const Camera &camera)
{
	GeometryBuffer.UnBind();
}

}}