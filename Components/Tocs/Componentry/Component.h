#pragma once
#include <string>
#include "ComponentMetaData.h"
#include "IComponent.h"

namespace Tocs {
namespace Componentry {

template <class C>
class Component : public IComponent
{

public:
	static ComponentMetaData<C> MetaData;

	Component(Entity *owner) : IComponent(owner) {}
	virtual ~Component() {}
};

template <class T>
ComponentMetaData<T> Component<T>::MetaData;

}}