#pragma once
#include "Pipe.h"
#include "TiledForwardPipe.h"
#include "WirePipe.h"
#include <string>
namespace Tocs {
namespace Rendering {

class RenderSystem;

class Pipeline
{

public:
	TiledForwardPipe ForwardPipe; 
	WirePipe WireframePipe;

	Pipeline(Graphics::GraphicsContext &context, RenderSystem &system);

};

}}