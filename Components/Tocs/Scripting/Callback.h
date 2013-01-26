#pragma once
#include <angelscript.h>
#include "Context.h"

class asIScriptFunction;

namespace Tocs {
namespace Scripting {

template <class>
class Callback;

template <class R>
class Callback <R ()>
{
	asIScriptFunction *Function;
public:
	Callback ()	: Function (0) {}
	void SetFunction (asIScriptFunction *func) { Function = func; }

	R Invoke (Context *context)
	{
		context->GetContextPtr()->Prepare (Function);
		context->ExecuteCall ();
		return context->GetReturnValue<R> ();
	}

	R InvokeMember (asIScriptObject *obj, Context*context)
	{
		context->GetContextPtr()->Prepare (Function);
		context->GetContextPtr()->SetObject (obj);
		context->ExecuteCall ();
		return context->GetReturnValue<R> ();
	}
};

template <class R, class A0>
class Callback <R (A0)>
{
	asIScriptFunction *Function;
public:
	Callback ()	: Function (0) {}
	void SetFunction (asIScriptFunction *func) { Function = func; }


	R Invoke (Context *context, A0 a0)
	{
		context->GetContextPtr()->Prepare (Function);
		context->SetArgValue(0,a0);
		context->ExecuteCall ();
		return context->GetReturnValue<R> ();
	}

	R InvokeMember (asIScriptObject *obj, Context*context, A0 a0)
	{
		context->GetContextPtr()->Prepare (Function);
		context->GetContextPtr()->SetObject (obj);
		context->SetArgValue(0,a0);
		context->ExecuteCall ();

		return context->GetReturnValue<R> ();
	}
};

template <class R, class A0, class A1>
class Callback <R (A0,A1)>
{
	asIScriptFunction *Function;
public:
	Callback ()	: Function (0) {}
	void SetFunction (asIScriptFunction *func) { Function = func; }

	R Invoke (Context *context, A0 a0, A1 a1)
	{
		context->GetContextPtr()->Prepare (Function);
		context->SetArgValue(0,a0);
		context->SetArgValue(1,a1);
		context->ExecuteCall ();

		return context->GetReturnValue<R> ();
	}

	R InvokeMember (asIScriptObject *obj, Context*context, A0 a0, A1 a1)
	{
		context->GetContextPtr()->Prepare (Function);
		context->GetContextPtr()->SetObject (obj);
		context->SetArgValue(0,a0);
		context->SetArgValue(1,a1);
		context->ExecuteCall ();
		return context->GetReturnValue<R> ();
	}
};

template <class R, class A0, class A1, class A2>
class Callback <R (A0,A1,A2)>
{
	asIScriptFunction *Function;
public:
	Callback ()	: Function (0) {}
	void SetFunction (asIScriptFunction *func) { Function = func; }

	R InvokeMember (asIScriptObject *obj, Context*context, A0 &&a0, A1 &&a1, A2 &&a2)
	{
		context->GetContextPtr()->Prepare (Function);
		context->GetContextPtr()->SetObject (obj);
		context->SetArgValue(0,a0);
		context->SetArgValue(1,a1);
		context->SetArgValue(1,a2);
		context->ExecuteCall ();
		return context->GetReturnValue<R> ();
	}
};


}}