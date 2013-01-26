#pragma once
#include <type_traits>
#include <vector>
#include "BufferBase.h"
#include "IntermediateEvent.h"


namespace Tocs {
namespace Parallel {

template <class T>
class Buffer
{
	BufferBase Base;
	Buffer(const Buffer<T> &);
	int _Length;
public:
	class WriteEvent : public IntermediateEvent
	{
		BufferBase &Base;
		unsigned int Offset;
		unsigned int Length;
		const T *Data;
		WriteEvent();
	protected:
		void Enqueue (CommandQueue &queue)
		{
			std::vector<Event> dependants = (Dependant != nullptr ? Dependant->GetResultEvents(queue) : std::vector<Event> ());
			ResultEvents.push_back (queue.WriteBuffer(Base,Offset*sizeof(T),Length*sizeof(T),(void *)Data,dependants));
		}

	public:
		WriteEvent (BufferBase &base, unsigned int offset, unsigned int length,const T *data)
			: Base(base), Offset(offset), Length(length), Data(data)
		{
		}
	
	};

	class ReadEvent : public IntermediateEvent
	{
		BufferBase &Base;
		unsigned int Offset;
		unsigned int Length;
		T *Dest;
	public:
		ReadEvent (BufferBase &base, unsigned int offset, unsigned int length, T *dest)
			: Base(base), Offset(offset), Length(length),Dest(dest)
		{
		}
	protected:
		void Enqueue (CommandQueue &queue)
		{
			std::vector<Event> dependants = (Dependant != nullptr ? Dependant->GetResultEvents(queue) : std::vector<Event> ());
			ResultEvents.push_back (queue.ReadBuffer(Base,Offset * sizeof(T),Length * sizeof(T),Dest,dependants));
		}
	};

	Buffer (Context &context, int element_count)
		: Base (context,BufferAccess::ReadWrite,sizeof(T) * element_count), _Length(element_count)
	{
		static_assert (std::is_trivial<T>::value, "Buffer types must be trivial. (See C++11 definition of trivial)");
	}

	Buffer (Buffer<T> &&moveme)
		: Base(std::move(moveme.Base))
	{
	}

	WriteEvent Write (unsigned int offset, unsigned length, T *data)
	{
		return WriteEvent (Base, offset, length, data);
	}

	WriteEvent Write (const std::vector<T> &data)
	{
		return WriteEvent (Base, 0, (data.size() < Length () ? data.size() : Length()), &data[0]);
	}

	ReadEvent Read (unsigned int offset, unsigned length, T *dest)
	{
		return ReadEvent (Base,offset,length,dest);
	}

	ReadEvent Read (std::vector<T> &dest)
	{
		//dest.resize (Length());
		return ReadEvent (Base,0,Length (),&dest[0]);
	}

	ReadEvent Read (std::vector<T> &dest, int offselt, int length)
	{
		//Resize?

		//return ReadEvent (Base,offset
	}


	unsigned int Length ()
	{
		return _Length;//Base.LengthInBytes () / sizeof (T);
	}

	_cl_mem *GetCLPtr () const { return Base.GetCLPtr (); }
};

}}