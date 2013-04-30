#pragma once
#include "Pipe.h"
#include "DeferredPipe.h"
namespace Tocs {
namespace Rendering {


class DeferredLightPipe : public Pipe
{
	const DeferredPipe &GBufferPipe;
protected:
	void BeginRendering (Graphics::GraphicsContext &context, const Camera &cam);
	void EndRendering   (Graphics::GraphicsContext &context, const Camera &cam);
public:
	DeferredLightPipe(const DeferredPipe &deferredpipe);
	void ApplyPipeInputs (Graphics::GraphicsContext &context, const Camera &cam, Graphics::Shader &shader);
};

}}