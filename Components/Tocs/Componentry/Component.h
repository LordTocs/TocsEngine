#pragma once
#include <cassert>
#include <Tocs/Core/FreeList.h>
namespace Tocs {
namespace Componentry {

class IComponentPool
{
public:
	virtual ~IComponentPool() {}

	virtual void Destroy(FreeListId id) = 0;
};

template <class ComponentType, class DeviceType>
class ComponentPool : public IComponentPool
{
	FreeList<ComponentType> Pool;
public:
	ComponentPool(const ComponentPool &) = delete;
	ComponentPool &operator= (const ComponentPool &) = delete;


	ComponentType &Get(FreeListId id) { return Pool.Get(id); }
	const ComponentType &Get(FreeListId id) const { return Pool.Get(id); }

	FreeListId Construct(DeviceType *device)
	{
		return Pool.Add(ComponentType(device));
	}

	void Destroy(FreeListId id) { Pool.Remove(id); }
};


template <class ComponentType, class DeviceType>
class Component
{
	DeviceType *Owner_;
public:
	static ComponentPool<ComponentType, DeviceType> Pool;

	Component(DeviceType *owner)
		: Owner_(owner) {}

	Component(const Component &) = delete;
	Component &operator=(const Component &) = delete;

	virtual ~Component() {}

	const DeviceType &Owner() const { return *Owner_; }
	DeviceType &Owner() { return *Owner_; }

};

template <class ComponentType, class DeviceType>
ComponentPool<ComponentType, DeviceType> Component<ComponentType,DeviceType>::Pool;

template <class DeviceType>
class ComponentLink
{
	unsigned int TypeHash_;
protected:
	IComponentPool *Pool;
	FreeListId ComponentID;
public:
	template<class ComponentType>
	ComponentLink(DeviceType *device)
	: TypeHash_(typeid(ComponentType).hash_code())
	, Pool(&Component<ComponentType,DeviceType>::Pool)
	, ComponentID(Component<ComponentType, DeviceType>::Pool.Construct(device))
	{}

	ComponentLink(ComponentLink &&moveme)
		: TypeHash_(moveme.TypeHash_)
		, Pool(moveme.Pool)
		, ComponentID(std::move(moveme.ComponentID))
	{}

	~ComponentLink()
	{
		if (ComponentID.IsValid())
			Pool->Destroy(ComponentID);
	}

	ComponentLink(const ComponentLink &) = delete;
	ComponentLink &operator= (const ComponentLink &) = delete;

	template <class T>
	T &Get()
	{
		assert(TypeHash_ != typeid(T).hash_code());
		Component<T, DeviceType>::Pool.Get(ComponentID);
	}

	template <class T>
	const T &Get() const
	{
		assert(TypeHash_ != typeid(T).hash_code());
		Component<T, DeviceType>::Pool.Get(ComponentID);
	}

	unsigned int TypeHash() const { return TypeHash_; }

	bool operator< (const ComponentLink<DeviceType> &other) const
	{
		return TypeHash_ < other.TypeHash_;
	}
};

}
}