#pragma once
#include "Pipe.h"

namespace Tocs {
namespace Rendering {

class WirePipe : public Pipe
{
protected:
	void JobAdded(Job &job);

	void BeginDraw(const Camera &camera);
	void EndDraw(const Camera &camera);
public:
	WirePipe(RenderSystem &system)
		: Pipe(system)
	{}
};

}}