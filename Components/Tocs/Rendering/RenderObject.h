#pragma once
#include "RenderSystem.h"
#include <Tocs/Math/Transform.h>
namespace Tocs {
namespace Rendering {

class RenderObject
{
protected:
	RenderSystem &System;
	virtual void QueueJobs () = 0;
	virtual void DequeueJobs () = 0;
public:
	Math::Transform Transform;
	RenderObject(RenderSystem &system);
	virtual ~RenderObject ();
	virtual void Update (float dt);

	RenderSystem &GetSystem () { return System; }
	const RenderSystem &GetSystem () const { return System; }
};

}}