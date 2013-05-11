#pragma once
#include "Pipe.h"
namespace Tocs {
namespace Rendering {

class WirePipe : public Pipe
{
protected:
	virtual void BeginRendering (Graphics::GraphicsContext &context, const Camera &cam);
	virtual void EndRendering   (Graphics::GraphicsContext &context, const Camera &cam);
public:
	virtual void ApplyPipeInputs (Graphics::GraphicsContext &context, const Camera &cam, Graphics::Shader &shader);
};

}}

