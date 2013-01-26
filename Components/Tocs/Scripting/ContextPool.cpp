#include "ContextPool.h"
#include "Engine.h"

namespace Tocs {
namespace Scripting {

Context *ContextPool::GetContext ()
{
	if (Contexts.size () != 0)
	{
		Context *ctx = *Contexts.rbegin ();
		Contexts.pop_back ();
		return ctx;
	}
	return ScriptEngine.CreateContext ();
}
void ContextPool::ReturnContext (Context *context)
{
	Contexts.push_back(context);
	context->GetContextPtr()->Unprepare ();
}

}}