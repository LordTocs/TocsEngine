#pragma once

struct _cl_event;

namespace Tocs {
namespace Parallel {

class Event
{
	_cl_event *EventPtr;
public:
	Event(const Event &copyme);
	Event(_cl_event *evt);
	~Event();

	Event &operator= (const Event& copyme);

	_cl_event *GetCLPtr () { return EventPtr; }

	void Wait () const;
};

}}