#pragma once
#include "Pipe.h"
#include "OpaqueForwardPipe.h"
#include "WirePipe.h"
#include <string>
namespace Tocs {
namespace Rendering {

class RenderSystem;

class Pipeline
{

public:
	OpaqueForwardPipe OpaquePipe;
	WirePipe WireframePipe;

	Pipeline(RenderSystem &system);

};

}}