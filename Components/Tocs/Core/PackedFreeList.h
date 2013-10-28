#pragma once
#include <vector>
#include <algorithm>
#include <limits>

namespace Tocs {

template <class T>
class PackedFreeList
{
public:
	class Id
	{
	public:
		unsigned int Index;
		Id () : Index(std::numeric_limits<unsigned int>::max()) {}

		Id (unsigned int index) : Index(index) {}

		bool IsValid () const { return Index != std::numeric_limits<unsigned int>::max(); }
	};
private:

	class IndexContainer
	{
	public:
		typename PackedFreeList<T>::Id ObjectId;
		unsigned int Index;
		unsigned int Next;
		IndexContainer (Id id, unsigned int next)
			: ObjectId(id), Next(next) {}

		bool IsValid () const { return Index != std::numeric_limits<unsigned int>::max(); }
	};

	class ObjectContainer
	{
	public:
		Id ObjectId;
		unsigned char Buffer [sizeof(T)];

		ObjectContainer ()
			: Buffer ()
		{}

		ObjectContainer (const T &object, Id id)
			: ObjectId (id)
		{
			new (&Buffer) T (object);
		}
		
		//~ObjectContainer?()

		T &Get ()
		{
			return *reinterpret_cast<T *> (&Buffer);
		}

		const T &Get () const
		{
			return *reinterpret_cast<const T *> (&Buffer);
		}

		void Destruct ()
		{
			Get().~T();
		}

		void Place (const T &object, Id id)
		{
			ObjectId = id;
			new (&Buffer) T (object);
		}

		void Place (T &&object, Id id)
		{
			ObjectId = id;
			new (&Buffer) T (std::forward(object));
		}

		bool operator < (const ObjectContainer &other)
		{
			return Get () < other.Get();
		}
	};
	std::vector<IndexContainer> Indices;
	std::vector<ObjectContainer> Objects;

	unsigned int List;


	void InsertNext (const T &value, unsigned int next)
	{
		if (next >= Objects.size())
		{
			Objects.push_back(value);
		}
	}
public:

	PackedFreeList()
		: List (std::numeric_limits<unsigned int>::max())
	{
	}

	~PackedFreeList ()
	{
		for (auto i = Objects.begin (); i != Objects.end(); ++i)
		{
			(*i).Destruct();
		}
	}

	Id Add (const T &object)
	{
		Id result;
		IndexContainer *in = nullptr;
		if (List == std::numeric_limits<unsigned int>::max()) //List is empty
		{
			result.Index = Indices.size();
			Indices.push_back(IndexContainer(result,std::numeric_limits<unsigned int>::max()));
			in = &Indices[Indices.size() - 1];
		}
		else
		{
			result.Index = List;
			Indices[List].ObjectId = result;
			in = &Indices[List];
			List = Indices[List].Next;
		}
		in->Index = Objects.size();
		Objects.push_back(ObjectContainer(object,result));

		return result;
	}

	void Remove (Id id)
	{
		if (!id.IsValid())
			return;

		IndexContainer &in = Indices[id.Index];
		in.Next = List;

		ObjectContainer &co = Objects[in.Index];
		co.Destruct(); //Destroy the object
		co = Objects[Objects.size() - 1]; //Shift the end down to the removed items spot
		Objects.pop_back(); //Remove the end

		//Fix the end's index
		Indices[co.ObjectId.Index].Index = in.Index;

		List = in.Index;

		//Invalidate the old index object
		in.Index = std::numeric_limits<unsigned int>::max();
	}

	const T &Get(Id id) const { return Objects[Indices[id.Index].Index].Get(); }
	T &Get(Id id) { return Objects[Indices[id.Index].Index].Get(); }
public:
	friend class ObjectIterator;

	class ObjectIterator
	{
		PackedFreeList<T> *List;
		unsigned int Index;

		ObjectIterator(PackedFreeList<T> *list, unsigned int index)
			: List(list), Index(index)
		{}
	public:
		friend class PackedFreeList<T>;

		ObjectIterator ()
			: List(nullptr), Index(std::numeric_limits<unsigned int>::max())
		{}

		T &operator *()
		{ return List->Objects[Index].Get(); }

		const T &operator *() const
		{ return List->Objects[Index].Get(); }

		T *operator->()
		{ return &(List->Objects[Index].Get());}

		const T *operator->() const
		{ return &(List->Objects[Index].Get());}

		Id GetId () const { return List->Objects[Index].ObjectId; }

		ObjectIterator operator++ (int)
		{
			ObjectIterator result(*this);
			++Index;
			return result;
		}

		ObjectIterator &operator++ ()
		{
			++Index;
			return *this;
		}

		bool operator== (const ObjectIterator &other) const
		{
			return other.List == List && other.Index == other.Index;
		}

		bool operator!= (const ObjectIterator &other) const
		{
			return other.List == List && other.Index != Index;
		}


	};

	ObjectIterator BeginObjects () { return ObjectIterator (this,0); }
	ObjectIterator EndObjects () { return ObjectIterator (this,Objects.size()); }


	void Sort ()
	{
		//abilabilabilabila
		std::sort(Objects.begin(),Objects.end());

		int index = 0;
		for (auto i = Objects.begin(); i != Objects.end(); ++i)
		{
			Indices[(*i).ObjectId.Index].Index = index;
			++index;
		}

	}
};

}