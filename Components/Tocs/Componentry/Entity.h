#pragma once
//#include <angelscript.h>
#include <vector>
#include "EntityType.h"
#include "World.h"

namespace Tocs {
namespace Componentry {

class IComponent;

class Entity
{
	std::vector<IComponent *> Components;
	EntityType *Type;
	asIScriptObject *ScriptObject;
	World &WorldPtr;
public:
	Entity(EntityType *type, World &world);
	~Entity(void);

	World &GetWorld () { return WorldPtr; }
	EntityType *GetType () { return Type; }
	asIScriptObject *GetScriptObject () { return ScriptObject; }
	IComponent *GetComponent (int i) { return Components[i]; }

	template <class C>
	C *GetComponent ()
	{
		for (auto i = Components.begin (); i != Components.end (); ++i)
		{
			C *result = dynamic_cast<C*> (*i);
			if (result != nullptr)
				return result;
		}
		return nullptr;
	}
};


}}

