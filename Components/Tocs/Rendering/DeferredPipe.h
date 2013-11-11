#pragma once
#include "Pipe.h"
#include "GBuffer.h"
namespace Tocs {
namespace Rendering {

class DeferredPipe : public Pipe
{
protected:
	void BeginJob(Job &job, Graphics::GraphicsContext &context, const Camera &camera);
	void EndJob(Job &job, Graphics::GraphicsContext &context, const Camera &camera);

	void BeginDraw(Graphics::GraphicsContext &context, const Camera &camera);
	void EndDraw(Graphics::GraphicsContext &context, const Camera &camera);
public:
	GBuffer GeometryBuffer;

	DeferredPipe();
};


}}