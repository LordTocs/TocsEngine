#pragma once
#include "Pipe.h"

namespace Tocs {
namespace Rendering {

class ShadowPipe : public Pipe
{
protected:
	void JobAdded(Job &job);

	void BeginJob(Job &job, const Camera &camera);
	void EndJob(Job &job, const Camera &camera);

	void BeginDraw(const Camera &camera);
	void EndDraw(const Camera &camera);
public:
	ShadowPipe(RenderSystem &system);
};

}}