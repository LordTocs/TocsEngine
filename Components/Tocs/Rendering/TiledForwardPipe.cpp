#include "TiledForwardPipe.h"
#include "RenderSystem.h"
namespace Tocs {
namespace Rendering {

TiledForwardPipe::TiledForwardPipe(RenderSystem &system, Graphics::GraphicsContext &context)
{

}

void TiledForwardPipe::JobAdded(Job &job)
{
	job.Input.ApplyMap(Grid.GetShaderInputs());
}
void TiledForwardPipe::BeginJob(Job &job, RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera)
{
	(*job.DrawShader)["View"] = camera.GetView();
	(*job.DrawShader)["Projection"] = camera.GetProjection();
}
void TiledForwardPipe::EndJob(Job &job, RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera)
{

}
void TiledForwardPipe::BeginDraw(RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera)
{
	Grid.Configure(camera, system.GetLights());
}
void TiledForwardPipe::EndDraw(RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera)
{

}

}}