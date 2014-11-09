#include "GlowPipe.h"
#include "RenderSystem.h"
namespace Tocs {
namespace Rendering {

void GlowPipe::BeginJob(Job &job, const Camera &camera)
{

}

void GlowPipe::EndJob(Job &job, const Camera &camera)
{
}

void GlowPipe::BeginDraw(const Camera &camera)
{
	System.GetPostProcesses().Glow.SetupGlowViewport(System.Context());
	System.GetPostProcesses().Glow.GetGlowTarget().Bind();
	System.Context().ClearColor(Math::Color(0, 0, 0));
	System.Context().ClearDepth();
	System.GetPostProcesses().Glow.ConvertDepthBuffer();

}

void GlowPipe::EndDraw(const Camera &camera)
{
	System.GetPostProcesses().Glow.GetGlowTarget().UnBind();
}

GlowPipe::GlowPipe(RenderSystem &system)
: Pipe(system)
{
}

}}