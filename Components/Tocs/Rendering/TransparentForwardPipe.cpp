#include "TransparentForwardPipe.h"
#include "RenderSystem.h"

namespace Tocs {
namespace Rendering {

void TransparentForwardPipe::JobAdded(Job &job)
{
	job.StateSet.MapState(System.GetAlphaBuffer().GetInputs());
}

void TransparentForwardPipe::BeginJob(Job &job, const Camera &camera)
{
}

void TransparentForwardPipe::EndJob(Job &job, const Camera &camera)
{
}

void TransparentForwardPipe::BeginDraw(const Camera &camera)
{
	System.Context().DisableDepthWrite();
	System.GetAlphaBuffer().Bind();
}

void TransparentForwardPipe::EndDraw(const Camera &camera)
{
	System.GetAlphaBuffer().UnBind();
	System.GetAlphaBuffer().CheckPageSizes(System);
	System.Context().EnableDepthWrite();
}

TransparentForwardPipe::TransparentForwardPipe(RenderSystem &system)
: Pipe(system)
{

}

}}