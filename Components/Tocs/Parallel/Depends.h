#pragma once
#include <vector>
#include "IntermediateEvent.h"
namespace Tocs {
namespace Parallel {

/*
class DependantEvents
{
	std::vector<Event> Events;
public:
	DependantEvents();
	~DependantEvents();

	void Add (const Event &evt)
	{ Events.push_back(evt); }

	int Count () { return Events.size (); }

	_cl_event *GetEventArray () { return reinterpret_cast<_cl_event*>(&Events[0]); }
};*/

class DependantEvents : IntermediateEvent
{
	std::vector<IntermediateEvent *> Events;
protected:
	void Enqueue (CommandQueue &queue)
	{
		for (auto i = Events.begin (); i != Events.end (); ++i)
		{
			std::vector<Event> evts = (*i)->GetResultEvents (queue);
			ResultEvents.insert(ResultEvents.end (), evts.begin(), evts.end());
		}
	}
public:
	DependantEvents();
	DependantEvents(DependantEvents &&copyme)
		: Events(std::move(copyme.Events))
	{
	}
	~DependantEvents();

	void Add (IntermediateEvent &evt)
	{ Events.push_back(&evt); }

	int Count () { return Events.size (); }
};

DependantEvents Do (IntermediateEvent &&one);
DependantEvents Do (IntermediateEvent &&one, IntermediateEvent &&two);
DependantEvents Do (IntermediateEvent &&one, IntermediateEvent &&two, IntermediateEvent &&three);


}}