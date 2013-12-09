#pragma once
#include <vector>
#include <Tocs/Core/PackedFreeList.h>
#include "Job.h"
#include "Camera.h"
#include <Tocs/Graphics/GraphicsContext.h>

namespace Tocs {
namespace Rendering {

class Pipe;
class RenderSystem;

class JobProxy
{
	Pipe *PipeRef;
	PackedFreeList<Job>::Id Id;
	JobProxy (Pipe *pipe, PackedFreeList<Job>::Id id)
		: PipeRef(pipe), Id (id) {}
public:
	friend class Pipe;

	JobProxy ()
		: PipeRef(nullptr) {}

	Job &Get ();
	const Job &Get() const;

	operator bool() const
	{
		return PipeRef != nullptr && Id.IsValid();
	}

	void Remove();

};

class Pipe
{
	PackedFreeList<Job> Jobs;
protected:
	virtual void JobAdded(Job &job) {}
	

	virtual void BeginJob(Job &job, RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera) = 0;
	virtual void EndJob  (Job &job, RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera) = 0;

	virtual void BeginDraw(RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera) = 0;
	virtual void EndDraw(RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera) = 0;
	
public:
	friend class JobProxy;
	Pipe();
	Pipe(const Pipe&) = delete;
	virtual ~Pipe () {}
	void Draw(RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera);

	JobProxy Add (DrawCall call, Graphics::Shader &shader);
	void Remove (const JobProxy &proxy);

};

}}