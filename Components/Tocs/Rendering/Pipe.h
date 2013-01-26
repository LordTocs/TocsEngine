#pragma once
#include <list>
#include "RenderJob.h"
#include "Camera.h"
namespace Tocs {
namespace Rendering {

class Pipe
{
	std::list<RenderJob*> Jobs;
protected:
	virtual void BeginRender (const Camera &camera, Graphics::GraphicsContext &context) {}
	virtual void EndRender (const Camera &camera, Graphics::GraphicsContext &context) {}
public:
	friend class RenderJob;

	Pipe();
	virtual ~Pipe();

	void AddJob (RenderJob &job)
	{
		Jobs.push_back(&job);
		job.Iterator = --Jobs.end (); 
		job.OwnerPipe = this;
	}

	void Render (const Camera &camera, Graphics::GraphicsContext &context);
};

}}
