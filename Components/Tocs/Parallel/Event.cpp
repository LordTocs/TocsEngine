#include "Event.h"
#include <CL/cl.h>

namespace Tocs {
namespace Parallel {

Event::Event (const Event& copyme)
	: EventPtr (copyme.EventPtr)
{
	clRetainEvent (EventPtr);
}

Event::Event(cl_event evt)
	: EventPtr (evt)
{
	clRetainEvent (evt);
}


Event::~Event(void)
{
	clReleaseEvent (EventPtr);
}

void Event::Wait () const
{
	clWaitForEvents (1,&EventPtr);
}

Event &Event::operator= (const Event& copyme)
{
	if (EventPtr != nullptr)
	{
		clReleaseEvent (EventPtr);
	}
	EventPtr = copyme.EventPtr;
	clRetainEvent (EventPtr);
	return *this;
}

}}