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
};

}}