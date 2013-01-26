#pragma once
#include "Context.h"
#include <vector>
namespace Tocs {
namespace Scripting {

class Engine;

class ContextPool
{
	Engine &ScriptEngine;
	std::vector<Context *> Contexts;
public:
	ContextPool(Engine &engine)
		: ScriptEngine (engine)
	{}

	Context *GetContext ();
	void ReturnContext (Context *context);
};

}}

