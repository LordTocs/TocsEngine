#pragma once
#include "Pipe.h"
#include "GBuffer.h"


namespace Tocs {
namespace Rendering {

class RenderSystem;

class DeferredPipe : public Pipe
{
	GBuffer Buffer;
protected:
	void BeginRendering (Graphics::GraphicsContext &context, const Camera &cam);
	void EndRendering   (Graphics::GraphicsContext &context, const Camera &cam);
public:
	DeferredPipe(Graphics::GraphicsContext &context, RenderSystem &system);
	
	GBuffer &GetBuffer () { return Buffer; }
	const GBuffer &GetBuffer () const { return Buffer; }

	void ApplyPipeInputs (Graphics::GraphicsContext &context, const Camera &cam, Graphics::Shader &shader);
};

}}

