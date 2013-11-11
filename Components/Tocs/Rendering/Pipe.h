#pragma once
#include <vector>
#include <Tocs/Core/PackedFreeList.h>
#include "Job.h"
#include "Camera.h"
#include <Tocs/Graphics/GraphicsContext.h>
namespace Tocs {
namespace Rendering {

class Pipe;

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
};

class Pipe
{
	PackedFreeList<Job> Jobs;
protected:
	virtual void BeginJob (Job &job, Graphics::GraphicsContext &context, const Camera &camera) = 0;
	virtual void EndJob   (Job &job, Graphics::GraphicsContext &context, const Camera &camera) = 0;

	virtual void BeginDraw (Graphics::GraphicsContext &context, const Camera &camera) = 0;
	virtual void EndDraw (Graphics::GraphicsContext &context, const Camera &camera) = 0;
	Pipe(const Pipe&);
public:
	friend class JobProxy;
	Pipe();
	virtual ~Pipe () {}
	void Draw (Graphics::GraphicsContext &context, const Camera &camera);

	JobProxy Add (const Job &job);
	void Remove (const JobProxy &proxy);

};

}}