#pragma once
#include "Pipe.h"
#include "OpaqueForwardPipe.h"
#include "WirePipe.h"
#include "TransparentForwardPipe.h"
#include "DeferredPipe.h"
#include "ShadowPipe.h"
#include "GlowPipe.h"
#include <string>
namespace Tocs {
namespace Rendering {

class RenderSystem;

class Pipeline
{

public:
	OpaqueForwardPipe OpaquePipe;
	WirePipe WireframePipe;
	TransparentForwardPipe TransparentPipe;
	DeferredPipe DeferredPipe;
	ShadowPipe ShadowPipe;
	GlowPipe GlowPipe;
	Pipeline(RenderSystem &system);

};

}}