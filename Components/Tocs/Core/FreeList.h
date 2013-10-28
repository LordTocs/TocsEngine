#pragma once
#include <vector>

template<class T>
class FreeList
{
public:
	class Id
	{
	public:
		unsigned int Index;
		unsigned int InnerId;
		Id () : Index(~0u), InnerId(~0u) {}

		bool IsValid () const { return Index != ~0u; }
	};
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
	};

	std::vector<Container> Objects;
	unsigned int List;
public:

	T &Get (const Id &id)
	{
		return Objects[id.Index].Value();
	}

	const T &Get (const Id &id) const
	{
		return Objects[id.Index].Value();
	}

	Id Add (const T &object)
	{
		Id id;
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
		}
		return id;
	}

	Id Add (T &&object)
	{
		Id id;
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

	void Remove (const Id &id)
	{
		Container &container = Objects[id.Index];
		container.Next = List;
		List = id.Index;
		Objects[List].Value().~T();
	}



};