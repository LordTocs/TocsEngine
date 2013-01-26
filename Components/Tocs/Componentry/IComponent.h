#pragma once
#include "Entity.h"

namespace Tocs {
namespace Componentry {

class IComponent
{
	Entity *Owner;
public:
	IComponent(Entity *owner) : Owner(owner) {}
	virtual ~IComponent() {}

	Entity *GetOwner () { return Owner; }
};



}}