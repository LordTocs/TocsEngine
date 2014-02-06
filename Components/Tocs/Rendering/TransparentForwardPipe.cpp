#include "TransparentForwardPipe.h"
#include "RenderSystem.h"

namespace Tocs {
namespace Rendering {

void TransparentForwardPipe::JobAdded(Job &job)
{
	job.Input.ApplyMap(System.GetAlphaBuffer().Inputs);
	//job.Input["ShadowMaps"].Ref(System.GetShadows().GetShadowMaps());
}

void TransparentForwardPipe::BeginJob(Job &job, const Camera &camera)
{
	(*job.DrawShader)["View"] = camera.GetView();
	(*job.DrawShader)["InvView"] = camera.GetInverseView();
	(*job.DrawShader)["Projection"] = camera.GetProjection();
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