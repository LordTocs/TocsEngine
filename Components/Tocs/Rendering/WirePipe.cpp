#include "WirePipe.h"

namespace Tocs {
namespace Rendering {

void WirePipe::JobAdded(Job &job)
{

}

void WirePipe::BeginJob(Job &job, RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera)
{
	(*job.DrawShader)["View"] = camera.GetView();
	(*job.DrawShader)["Projection"] = camera.GetProjection();
}

void WirePipe::EndJob(Job &job, RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera)
{

}

void WirePipe::BeginDraw(RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera)
{
	context.EnableWireframe();
}

void WirePipe::EndDraw(RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera)
{
	context.DisableWireframe();
}

}}