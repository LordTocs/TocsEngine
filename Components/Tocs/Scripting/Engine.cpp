#include "Engine.h"
#include "scriptstdstring.h"
#include "Context.h"
#include <iostream>

using namespace std;

namespace Tocs {
namespace Scripting {


Engine::Engine(void)
	: EnginePtr (asCreateScriptEngine(ANGELSCRIPT_VERSION)),
	  Pool (*this)
{
	int r = 1;
	r = EnginePtr->SetMessageCallback(asMETHOD(Engine,MessageCallback),this,asCALL_THISCALL);

	RegisterStdString(EnginePtr);
}


Engine::~Engine(void)
{
}


void Engine::MessageCallback(const asSMessageInfo &msg)
{
	const char *type = "ERR ";
	if( msg.type == asMSGTYPE_WARNING ) 
		type = "WARN";
	else if( msg.type == asMSGTYPE_INFORMATION ) 
		type = "INFO";

	cout << msg.section << " (" << msg.row << ", " << msg.col << ") : " << type << " : " << msg.message << endl;

}

Context *Engine::CreateContext ()
{
	return new Context (*this);
}

}}