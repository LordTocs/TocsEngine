#pragma once
#include "Pipe.h"
#include "DeferredPipe.h"
#include <Tocs/Graphics/RenderTarget.h>
namespace Tocs {
namespace Rendering {


class DeferredLightPipe : public Pipe
{
	const DeferredPipe &GBufferPipe;
	Graphics::RenderTarget &ResultTarget;
protected:
	void BeginRendering (Graphics::GraphicsContext &context, const Camera &cam);
	void EndRendering   (Graphics::GraphicsContext &context, const Camera &cam);
public:
	DeferredLightPipe(Graphics::GraphicsContext &context, RenderSystem &system);
	void ApplyPipeInputs (Graphics::GraphicsContext &context, const Camera &cam, Graphics::Shader &shader);
};

}}