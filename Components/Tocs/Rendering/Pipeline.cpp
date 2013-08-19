#include "Pipeline.h"


namespace Tocs {
namespace Rendering {

Pipeline::Pipeline (Graphics::GraphicsContext &context, RenderSystem &system)
	: DeferredPipe (context,system),
	  DeferredLightPipe (context, system)
{
}

Pipe *Pipeline::GetPipeByName (const std::string &name)
{
	if (name == "NonLit")
	{
		return &UnlitPipe;
	}
	else if (name == "Deferred")
	{
		return &DeferredPipe;
	}
	else if (name == "DeferredLight")
	{
		return &DeferredLightPipe;
	}
	else if (name == "Wireframe")
	{
		return &WireframePipe;
	}
}


}}
