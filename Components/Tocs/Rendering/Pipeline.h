#pragma once
#include "NonLitPipe.h"
#include "DeferredPipe.h"
#include "DeferredLightPipe.h"

namespace Tocs {
namespace Rendering {

class Pipeline
{
	Pipeline (const Pipeline &);
public:
	Pipeline (Graphics::GraphicsContext &context);

	NonLitPipe NonLitPipe;
	DeferredPipe DeferredPipe;
	DeferredLightPipe DeferredLightPipe;

	Pipe *GetPipeByName (const std::string &name);
};

}}