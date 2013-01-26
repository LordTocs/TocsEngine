#pragma once
#include <string>
#include <vector>
#include <Tocs/Scripting/Engine.h>
#include "ComponentFactory.h"

namespace Tocs {
namespace Componentry {

class Entity;

class EntityType
{
	std::vector<IComponentFactory*> Components;

	void RegisterScriptType (Scripting::Engine &engine);
	void Parse (std::string entity_file, Scripting::Engine &engine);

	asIScriptModule *Module;
	asIObjectType *ScriptType;

	asIScriptObject *ConstructScriptObject (Entity *ent);

	std::string Name;
public:
	const std::string &GetName () { return Name; }

	EntityType(std::string entity_file, Scripting::Engine &engine);
	~EntityType();

	friend class Entity;
};

}}