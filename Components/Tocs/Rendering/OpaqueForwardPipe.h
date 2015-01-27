#pragma once
#include "LightGrid.h"
#include "Pipe.h"

namespace Tocs {
namespace Rendering {

class OpaqueForwardPipe : public Pipe
{
protected:
	void JobAdded(Job &job);

	void BeginDraw(const Camera &camera);
	void EndDraw(const Camera &camera);
public:
	OpaqueForwardPipe(RenderSystem &system);
};

}}