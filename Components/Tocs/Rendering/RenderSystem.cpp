#include "RenderSystem.h"
#include "DeferredPipe.h"

namespace Tocs {
namespace Rendering {

RenderSystem::RenderSystem()
{
	
}

RenderSystem::~RenderSystem(void)
{
}

void RenderSystem::Render (const Camera &cam, Graphics::GraphicsContext &context)
{
	Pipes.Deferred.Render (cam,context);

	Pipes.Lights.Render (cam,context);
}

}}
