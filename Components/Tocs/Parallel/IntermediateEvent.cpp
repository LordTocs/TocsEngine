#include "IntermediateEvent.h"

namespace Tocs {
namespace Parallel {


std::vector<Event> IntermediateEvent::GetResultEvents (CommandQueue &queue)
{
	if (Enqueued)
		return ResultEvents;
	else
	{
		Enqueued = true;
		Enqueue (queue);
	}

	return ResultEvents;
}

}}