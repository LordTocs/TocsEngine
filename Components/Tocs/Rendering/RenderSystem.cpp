#include "RenderSystem.h"

namespace Tocs {
namespace Rendering {

RenderSystem::RenderSystem(Graphics::GraphicsContext  &context)
	: Pipes(context)
{
}

void RenderSystem::Render (Graphics::GraphicsContext &context,const Camera &cam)
{
	Pipes.DeferredPipe.Render (context,cam);
	Pipes.DeferredLightPipe.Render (context,cam);
	Pipes.NonLitPipe.Render (context,cam);
}

void RenderSystem::Update (float dt)
{	
}

}}