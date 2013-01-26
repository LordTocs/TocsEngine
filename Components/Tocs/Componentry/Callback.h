#pragma once
#include <Tocs/Scripting/Callback.h>
#include <Tocs/Scripting/Engine.h>
#include "IComponent.h"
namespace Tocs {
namespace Componentry {

template <class>
class Callback;

template <class R>
class Callback <R()>
{
	IComponent *Owner;
	Tocs::Scripting::Callback <R()> ScriptCallback;
public:
	Callback (IComponent *owner)
		: Owner(owner) {}

	void SetFunction (asIScriptFunction *function)
	{ ScriptCallback.SetFunction (function); }

	R operator () ()
	{
		Tocs::Scripting::Context *context = Owner->GetOwner()->GetWorld ()->GetEngine().Pool.GetContext ();
		const R& returnvalue = ScriptCallback.InvokeMember (Owner->GetOwner ()->GetScriptObject (),context);
		Owner->GetOwner()->GetWorld ()->GetEngine().Pool.ReturnContext(context);
		return returnvalue;
	}
};

template <class R,class A0>
class Callback <R(A0)>
{
	IComponent *Owner;
	Tocs::Scripting::Callback <R(A0)> ScriptCallback;
public:
	void SetFunction (asIScriptFunction *function)
	{ ScriptCallback.SetFunction (function); }

	R operator () (A0 a0)
	{
		Tocs::Scripting::Context *context = Owner->GetOwner()->GetWorld ().GetEngine().Pool.GetContext ();
		const R& returnvalue = ScriptCallback.InvokeMember (Owner->GetOwner ()->GetScriptObject (),context,a0);
		Owner->GetOwner()->GetWorld ().GetEngine().Pool.ReturnContext(context);
		return returnvalue;
	}
};

template <class R, class A0, class A1>
class Callback <R(A0,A1)>
{
	IComponent *Owner;
	Tocs::Scripting::Callback <R(A0,A1)> ScriptCallback;
public:
	void SetFunction (asIScriptFunction *function)
	{ ScriptCallback.SetFunction (function); }

	R operator () (A0 a0, A1 a1)
	{
		Tocs::Scripting::Context *context = Owner->GetOwner()->GetWorld ()->GetEngine().Pool.GetContext ();
		const R& returnvalue = ScriptCallback.InvokeMember (Owner->GetOwner ()->GetScriptObject (),context,a0,a1);
		Owner->GetOwner()->GetWorld ()->GetEngine().Pool.ReturnContext(context);
		return returnvalue;
	}
};

template <class R, class A0, class A1, class A2>
class Callback <R(A0,A1,A2)>
{
	IComponent *Owner;
	Tocs::Scripting::Callback <R(A0,A1,A2)> ScriptCallback;
public:
	void SetFunction (asIScriptFunction *function)
	{ ScriptCallback.SetFunction (function); }

	R operator () (A0 a0, A1 a1, A2 a2)
	{
		Tocs::Scripting::Context *context = Owner->GetOwner()->GetWorld ()->GetEngine().Pool.GetContext ();
		const R& returnvalue = ScriptCallback.InvokeMember (Owner->GetOwner ()->GetScriptObject (),context,a0,a1,a2);
		Owner->GetOwner()->GetWorld ()->GetEngine().Pool.ReturnContext(context);
		return returnvalue;
	}
};

}}