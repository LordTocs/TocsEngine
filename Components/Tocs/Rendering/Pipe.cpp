#include "Pipe.h"
#include "Job.h"

namespace Tocs {
namespace Rendering {

void Pipe::Render (Graphics::GraphicsContext &context, const Camera &cam)
{
	BeginRendering (context,cam);
	for (auto i = Jobs.begin (); i != Jobs.end (); ++i)
	{
		(*i)->Render (context,cam);
	}
	EndRendering (context,cam);
}

void Pipe::RemoveJob (Job &job)
{
	Jobs.remove (&job);
}

void Pipe::AppendJob (Job &job)
{
	Jobs.push_back (&job);
	job.ListIterator = (--Jobs.end());
	job.Pipe = this;
}
}}