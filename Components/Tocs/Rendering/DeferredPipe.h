#pragma once
#include "Pipe.h"
#include "GBuffer.h"


namespace Tocs {
namespace Rendering {

class DeferredPipe : public Pipe
{
	GBuffer Buffer;
protected:
	void BeginRender (const Camera &camera, Graphics::GraphicsContext &context);
	void EndRender (const Camera &camera, Graphics::GraphicsContext &context);
public:
	DeferredPipe(Graphics::GraphicsContext &context);
	
	GBuffer &GetBuffer () { return Buffer; }
	const GBuffer &GetBuffer () const { return Buffer; }
};

}}

