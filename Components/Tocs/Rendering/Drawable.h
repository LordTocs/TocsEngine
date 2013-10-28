#pragma once
#include "RenderSystem.h"

namespace Tocs {
namespace Rendering {

class Drawable
{
public:
	Drawable(RenderSystem &system);
	virtual ~Drawable() {}

	virtual void QueueJobs () = 0;
	virtual void DeQueueJobs () = 0;
};

}}