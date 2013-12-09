#pragma once
#include "Pipe.h"
#include "GBuffer.h"
namespace Tocs {
namespace Rendering {

class DeferredPipe : public Pipe
{
protected:
	void BeginJob(Job &job, RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera);
	void EndJob(Job &job, RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera);

	void BeginDraw(RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera);
	void EndDraw(RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera);
public:
	GBuffer GeometryBuffer;

	DeferredPipe(RenderSystem &system, Graphics::GraphicsContext &context);
};


}}