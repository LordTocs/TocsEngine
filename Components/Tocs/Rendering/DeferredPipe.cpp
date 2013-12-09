#include "DeferredPipe.h"

namespace Tocs {
namespace Rendering {

DeferredPipe::DeferredPipe(RenderSystem &system, Graphics::GraphicsContext &context)
: GeometryBuffer(context,system)
{

}

void DeferredPipe::BeginJob(Job &job, RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera)
{
	(*job.DrawShader)["View"] = camera.GetView();
	(*job.DrawShader)["Projection"] = camera.GetProjection();
}
void DeferredPipe::EndJob(Job &job, RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera)
{

}

void DeferredPipe::BeginDraw(RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera)
{
	GeometryBuffer.Bind();
}
void DeferredPipe::EndDraw(RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera)
{
	GeometryBuffer.UnBind();
}

}}