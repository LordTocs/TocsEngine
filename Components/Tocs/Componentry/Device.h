#pragma once
#include "Component.h"
#include <algorithm>

namespace Tocs {
namespace Componentry {

template <class DeviceType>
class Device
{
	std::vector<ComponentLink<DeviceType>> Components;
public:
	virtual ~Device() {}

	template <class ComponentType>
	void AddComponent()
	{
		unsigned int hash = typeid(ComponentType).hash_code();
		auto i = std::lower_bound(Components.begin(), Components.end(), hash);
		Components.emplace(i, ComponentLink<DeviceType><ComponentType>());
	}

	template <class ComponentType>
	ComponentType &GetComponent()
	{
		unsigned int hash = typeid(ComponentType).hash_code();
		auto i = std::lower_bound(Components.begin(), Components.end(), hash);
		
		if (i == Components.end())
		{ assert(false); }

		if (i->TypeHash() != hash)
		{ assert(false); }

		return i->Get<ComponentType>();
	}

	template <class ComponentType>
	const ComponentType &GetComponent() const
	{
		unsigned int hash = typeid(ComponentType).hash_code();
		auto i = std::lower_bound(Components.begin(), Components.end(), hash);

		if (i == Components.end())
		{
			assert(false);
		}

		if (i->TypeHash() != hash)
		{
			assert(false);
		}

		return i->Get<ComponentType>();
	}

	template <class ComponentType>
	bool HasComponent() const
	{
		unsigned int hash = typeid(ComponentType).hash_code();
		auto i = std::lower_bound(Components.begin(), Components.end(), hash);

		if (i == Components.end())
		{
			return false;
		}

		if (i->TypeHash() != hash)
		{
			return false;
		}
	
		return true;
	}
};

}}