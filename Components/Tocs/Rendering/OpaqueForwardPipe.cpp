#include "OpaqueForwardPipe.h"
#include "RenderSystem.h"

namespace Tocs {
namespace Rendering {

OpaqueForwardPipe::OpaqueForwardPipe(RenderSystem &system)
: Pipe(system)
{

}

void OpaqueForwardPipe::JobAdded(Job &job)
{
	job.Input.ApplyMap(System.GetLightTiles().GetShaderInputs());
}
void OpaqueForwardPipe::BeginJob(Job &job, const Camera &camera)
{
	(*job.DrawShader)["View"] = camera.GetView();
	(*job.DrawShader)["Projection"] = camera.GetProjection();
}
void OpaqueForwardPipe::EndJob(Job &job, const Camera &camera)
{

}
void OpaqueForwardPipe::BeginDraw(const Camera &camera)
{
}

void OpaqueForwardPipe::EndDraw(const Camera &camera)
{

}

}}