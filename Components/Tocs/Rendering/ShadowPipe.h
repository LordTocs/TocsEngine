#pragma once
#include "Pipe.h"

namespace Tocs {
namespace Rendering {

class ShadowPipe : public Pipe
{
protected:
	void JobAdded(Job &job);

	void BeginDraw(const Camera &camera);
	void EndDraw(const Camera &camera);
public:
	ShadowPipe(RenderSystem &system);
};

}}