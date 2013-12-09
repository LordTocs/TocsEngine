#pragma once
#include "LightGrid.h"
#include "Pipe.h"

namespace Tocs {
namespace Rendering {

class TiledForwardPipe : public Pipe
{
	LightGrid Grid;
protected:
	void JobAdded(Job &job);

	void BeginJob(Job &job, RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera);
	void EndJob(Job &job, RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera);

	void BeginDraw(RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera);
	void EndDraw(RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera);
public:
	TiledForwardPipe(RenderSystem &system, Graphics::GraphicsContext &context);
};

}}