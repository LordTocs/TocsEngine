#pragma once
#include "Pipe.h"
namespace Tocs {
namespace Rendering {

class GlowPipe : public Pipe
{
protected:
	void BeginJob(Job &job, const Camera &camera);
	void EndJob(Job &job, const Camera &camera);

	void BeginDraw(const Camera &camera);
	void EndDraw(const Camera &camera);
public:


	GlowPipe(RenderSystem &system);
};

}}