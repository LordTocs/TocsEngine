#pragma once
#include "Pipe.h"

namespace Tocs {
namespace Rendering {


class TransparentForwardPipe : public Pipe
{
protected:
	void JobAdded(Job &job);

	void BeginJob(Job &job, const Camera &camera);
	void EndJob(Job &job, const Camera &camera);

	void BeginDraw(const Camera &camera);
	void EndDraw(const Camera &camera);
public:
	TransparentForwardPipe(RenderSystem &system);
};


}}