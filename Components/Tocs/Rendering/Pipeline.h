#pragma once
#include "NonLitPipe.h"
#include "WirePipe.h"
#include "DeferredPipe.h"
#include "DeferredLightPipe.h"

namespace Tocs {
namespace Rendering {

class Pipeline
{
	Pipeline (const Pipeline &);
public:
	Pipeline (Graphics::GraphicsContext &context);

	NonLitPipe UnlitPipe;
	WirePipe WireframePipe;
	DeferredPipe DeferredPipe;
	DeferredLightPipe DeferredLightPipe;

	Pipe *GetPipeByName (const std::string &name);
};

}}