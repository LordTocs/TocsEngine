#pragma once
#include "CommandQueue.h"
#include "Event.h"

namespace Tocs {
namespace Parallel {

class IntermediateEvent
{
protected:
	IntermediateEvent *Dependant;
	bool Enqueued;

	std::vector<Event> ResultEvents;
	virtual void Enqueue (CommandQueue &queue) = 0;
public:
	IntermediateEvent ()
		: Dependant (nullptr),
		  Enqueued (false)
	{}

	virtual ~IntermediateEvent() {}

	std::vector<Event> GetResultEvents (CommandQueue &queue);

	IntermediateEvent &Then (IntermediateEvent &evt)
	{
		evt.Dependant = this;
		return evt;
	}
};



}}