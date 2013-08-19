#pragma once
#include "Pipe.h"
#include "DeferredPipe.h"
#include <Tocs/Graphics/RenderTarget.h>

namespace Tocs {
namespace Rendering {

class GlowPipe : public Pipe
{
	Graphics::RenderTarget GlowTarget;
	Graphics::Texture2D AccumlationBuffer;
public:
	GlowPipe();
protected:
	void BeginRendering (Graphics::GraphicsContext &context, const Camera &cam);
	void EndRendering   (Graphics::GraphicsContext &context, const Camera &cam);
public:
	GlowPipe(Graphics::GraphicsContext &context, const DeferredPipe &deferredpipe);
	void ApplyPipeInputs (Graphics::GraphicsContext &context, const Camera &cam, Graphics::Shader &shader);

	const Graphics::Texture2D &GetAccumlationBuffer () const { return AccumlationBuffer; }
};

}}