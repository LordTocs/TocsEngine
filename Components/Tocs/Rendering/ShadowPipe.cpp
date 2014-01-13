#include "ShadowPipe.h"


namespace Tocs {
namespace Rendering {

void ShadowPipe::JobAdded(Job &job)
{

}

void ShadowPipe::BeginJob(Job &job, const Camera &camera)
{
	(*job.DrawShader)["View"] = camera.GetView();
	(*job.DrawShader)["Projection"] = camera.GetProjection();
}

void ShadowPipe::EndJob(Job &job, const Camera &camera)
{

}

void ShadowPipe::BeginDraw(const Camera &camera)
{

}
void ShadowPipe::EndDraw(const Camera &camera)
{

}

ShadowPipe::ShadowPipe(RenderSystem &system)
: Pipe(system)
{

}


}}