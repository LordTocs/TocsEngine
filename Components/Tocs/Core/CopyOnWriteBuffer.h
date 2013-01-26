#pragma once

namespace Tocs {

template <class T>
class CopyOnWriteBuffer
{
	int* ReferenceCount;
	T *Payload;
public:
	CopyOnWriteBuffer ()
		: Payload (new T ()),
		  ReferenceCount (new int (1))
	{}

	CopyOnWriteBuffer (const CopyOnWriteBuffer &clone)
		: ReferenceCount (clone.ReferenceCount),
		  Payload (clone.Payload)
	{
		++(*ReferenceCount);
	}
	CopyOnWriteBuffer (T *Payload)
		: ReferenceCount (new int (1)),
		  Payload (Payload)
	{}

	~CopyOnWriteBuffer ()
	{
		DeleteReference ();
	}

	T &GetPayload () const { return *Payload; }

	void SetPayload (T *payload) 
	{ 
		DeleteReference ();
		Payload = payload;
		ReferenceCount = new int (1); 
	}

	void SharePayload (const CopyOnWriteBuffer <T> &buffer)
	{
		if (&buffer == this)
			return;

		DeleteReference ();

		Payload = buffer.Payload;
		ReferenceCount = buffer.ReferenceCount;

		if (ReferenceCount != nullptr)
			++(*ReferenceCount);
	}

	void PrepareWrite ()
	{
		if ((*ReferenceCount) == 1)
			return;

		T *NewLoad = new T (*Payload);
		int *NewCount = new int (1);

		--(*ReferenceCount);
		Payload = NewLoad;
		ReferenceCount = NewCount;
	}
	void DeleteReference ()
	{
		if ((*ReferenceCount) > 1)
		{
			--(*ReferenceCount);
			return;
		}
		
		delete Payload;
		delete ReferenceCount;
	}
};

}