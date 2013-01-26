#pragma once
#include <angelscript.h>
#include "ContextPool.h"

namespace Tocs {
namespace Scripting {

class Context;

class Engine
{
	asIScriptEngine *EnginePtr;
	
	void MessageCallback(const asSMessageInfo &msg);
public:
	ContextPool Pool;

	Engine();
	~Engine();

	Context *CreateContext ();

	asIScriptEngine *GetEnginePtr () { return EnginePtr; }

	

};

}}
