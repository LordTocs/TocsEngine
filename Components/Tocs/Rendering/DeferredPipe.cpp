#include "DeferredPipe.h"

namespace Tocs {
namespace Rendering {

DeferredPipe::DeferredPipe()
{

}

void DeferredPipe::BeginJob(Job &job, Graphics::GraphicsContext &context, const Camera &camera)
{
	(*job.DrawShader)["View"] = camera.GetView();
	(*job.DrawShader)["Projection"] = camera.GetProjection();
}
void DeferredPipe::EndJob(Job &job, Graphics::GraphicsContext &context, const Camera &camera)
{

}

void DeferredPipe::BeginDraw(Graphics::GraphicsContext &context, const Camera &camera)
{
	GeometryBuffer.Bind();
}
void DeferredPipe::EndDraw(Graphics::GraphicsContext &context, const Camera &camera)
{
	GeometryBuffer.UnBind();
}

}}