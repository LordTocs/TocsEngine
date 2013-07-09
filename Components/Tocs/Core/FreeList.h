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
		T Value;
		unsigned int Next;
		Container (const T &value)
			: Value(value), Next(~0u) {}
		Container (T &&value)
			: Value (std::forward(value)), Next(~0u)
		{}
	};

	std::vector<Container> Objects;
	unsigned int List;
public:

	T &Get (const Id &id)
	{
		return Objects[id.Index].Value;
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
		Objects[List].Value.~T();
	}


};