#pragma once
#include "Pipe.h"
#include <map>
#include <string>
#include <type_traits>
#include "DeferredPipe.h"
#include "LightPipe.h"
namespace Tocs {
namespace Rendering {

class Pipeline
{
	Pipeline (const Pipeline &); //NO COPYING
public:

	Pipeline(Graphics::GraphicsContext &context);

	DeferredPipe Deferred;
	LightPipe Lights;
	
};

}}