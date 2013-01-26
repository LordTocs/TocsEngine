#pragma once
#include <Tocs/Scripting/Engine.h>
#include "TypeRegistry.h"
namespace Tocs {
namespace Componentry {

class World
{
	Tocs::Scripting::Engine ScriptingEngine;
public:
	TypeRegistry Types;

	World();
	~World();

	Tocs::Scripting::Engine &GetEngine () { return ScriptingEngine; }
};

}}

