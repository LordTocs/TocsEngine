#include "Entity.h"

namespace Tocs {
namespace Componentry {

Entity::Entity(EntityType *type, World &world)
	: Type(type), WorldPtr (world)
{
	Components.reserve(Type->Components.size());
	for (auto i = Type->Components.begin (); i != Type->Components.end (); ++i)
	{
		Components.push_back((*i)->Get (this));
	}
	ScriptObject = type->ConstructScriptObject(this);
}


Entity::~Entity(void)
{
}

}}
