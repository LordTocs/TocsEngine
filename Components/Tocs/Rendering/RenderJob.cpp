#include "RenderJob.h"
#include "Pipe.h"

namespace Tocs {
namespace Rendering {

RenderJob::~RenderJob(void)
{
	Remove ();
}

void RenderJob::Remove ()
{
	if (OwnerPipe == nullptr)
		return;
	OwnerPipe->Jobs.erase(Iterator);
	Iterator = OwnerPipe->Jobs.end ();
	OwnerPipe = nullptr;
}

}}