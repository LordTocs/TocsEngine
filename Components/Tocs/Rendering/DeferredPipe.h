#pragma once
#include "Pipe.h"
#include "GBuffer.h"
namespace Tocs {
namespace Rendering {

class DeferredPipe : public Pipe
{
protected:
	void BeginJob(Job &job, const Camera &camera);
	void EndJob(Job &job, const Camera &camera);

	void BeginDraw(const Camera &camera);
	void EndDraw(const Camera &camera);
public:
	

	DeferredPipe(RenderSystem &system);
};


}}