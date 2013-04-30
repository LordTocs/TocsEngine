#include "Pipeline.h"


namespace Tocs {
namespace Rendering {

Pipeline::Pipeline (Graphics::GraphicsContext &context)
	: NonLitPipe (),
	  DeferredPipe (context),
	  DeferredLightPipe (DeferredPipe)
{
}

Pipe *Pipeline::GetPipeByName (const std::string &name)
{
	if (name == "NonLit")
	{
		return &NonLitPipe;
	}
	else if (name == "Deferred")
	{
		return &DeferredPipe;
	}
	else if (name == "DeferredLight")
	{
		return &DeferredLightPipe;
	}
}


}}
