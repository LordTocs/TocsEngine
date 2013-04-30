#pragma once
#include <vector>

namespace Tocs {
namespace Rendering {

template <class>
class StateChange;

//Represents once graphics card state
template <class T,void T::(*statefunc)()>
class StateChange
{
	T *Instance;
public:
	static void Invoke (StateChange *change)
	{ change->Instance->*statefunc (); }
};


class StateSet
{
	class Entry
	{
		void *Change;
		void (*Invoke)();
	public:


		template <class SCT>
		Entry (SCT &change)
		{
			Change = reinterpret_cast<void*> (&change);
			Invoke = []() { SCT::Invoke (reinterpret_cast<SCT> (Change)); }
		}

		void Change ()
		{ 
			if (Invoke)
				Invoke (); 
		}
	};

	std::vector<Entry> Entries;

	template <class T, void T::(*statefunc)()>
	void Add (T &)
	{
		new Entry<StateChange <T,statefunc>> (StateChange
	}
};

}}
