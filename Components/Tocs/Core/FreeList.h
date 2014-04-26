#pragma once
#include <vector>

class FreeListId
{
public:
	unsigned int Index;
	unsigned int InnerId;
	FreeListId() : Index(~0u), InnerId(~0u) {}
	FreeListId(FreeListId &&moveme)
		: Index(moveme.Index), InnerId(moveme.InnerId)
	{
		Index = ~0u;
		InnerId = ~0u;
	}

	bool IsValid() const { return Index != ~0u; }
};

template<class T>
class FreeList
{
public:
	
private:
	unsigned int NextInnerId;
	class Container
	{
	public:
		unsigned char ValueContainer [sizeof(T)];
		unsigned int Next;
		Container (const T &value)
			: Value(),
			  Next(~0u) 
		{
			new (&ValueContainer[0]) T (value);
		}
		Container (T &&value)
			:  Next(~0u)
		{
			new (&ValueContainer[0]) T (std::forward(value));
		}
		~Container ()
		{
			if (HasValue())
				Value().~T();
		}

		T &Value ()
		{
			return *(reinterpret_cast<T *>(&ValueContainer[0]));
		}

		const T &Value () const
		{
			return *(reinterpret_cast<T *>(&ValueContainer[0]));
		}

		bool HasValue() const
		{
			return Next == ~0u;
		}
	};

	std::vector<Container> Objects;
	unsigned int List;
public:

	T &Get(const FreeListId &id)
	{
		return Objects[id.Index].Value();
	}

	const T &Get(const FreeListId &id) const
	{
		return Objects[id.Index].Value();
	}

	FreeListId Add(const T &object)
	{
		FreeListId id;
		id.InnerId = NextInnerId++;
		if(List == (~0u))
		{
			id.Index = Objects.size();
			Objects.push_back(Container(object));
		}
		else
		{
			id.Index = List;
			new (&Objects[List].Value) T (object);
			List = Objects[List].Next;
			Objects[List].Next = ~0u;
		}
		return id;
	}

	FreeListId Add(T &&object)
	{
		FreeListId id;
		id.InnerId = NextInnerId++;
		if(List == (~0u))
		{
			id.Index = Objects.size();
			Objects.push_back(Container(std::forward(object)));
		}
		else
		{
			id.Index = List;
			new (&Objects[List].Value) T (std::forward(object));
			List = Objects[List].Next;
		}
		return id;
	}

	void Remove(const FreeListId &id)
	{
		Container &container = Objects[id.Index];
		container.Next = List;
		List = id.Index;
		Objects[List].Value().~T();
	}



};