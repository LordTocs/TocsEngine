#pragma once
#include "Pipe.h"
#include "GBuffer.h"
#include <Tocs/Graphics/RenderTarget.h>

namespace Tocs {
namespace Rendering {

class Rendersystem;

class TransparentPipe : public Pipe
{
protected:
	void BeginRendering (Graphics::GraphicsContext &context, const Camera &cam);
	void EndRendering   (Graphics::GraphicsContext &context, const Camera &cam);
public:
	TransparentPipe(Graphics::GraphicsContext &context);
	void ApplyPipeInputs (Graphics::GraphicsContext &context, const Camera &cam, Graphics::Shader &shader);
};

}}

