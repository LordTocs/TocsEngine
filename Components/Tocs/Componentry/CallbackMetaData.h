#pragma once
#include <string>
#include "IComponent.h"

class asIScriptFunction;

#include "Callback.h"

namespace Tocs {
namespace Componentry {

template <class C>
class ICallbackMetaData
{
	std::string Name;
protected:
	asIScriptFunction *ScriptFunction;
public:
	

	ICallbackMetaData (const std::string &name)
		: Name(name)
	{}

	const std::string &GetName() { return Name; }

	virtual void SetFunction (asIScriptFunction *function) = 0;
	virtual void ApplyFunction (IComponent *component) = 0;
};

//template <class,class>
//class CallbackMetaData;

template <class C, class R, Callback<R()> C::*CallbackPtr>
class CallbackMetaData0 : public ICallbackMetaData <C>
{
public:
	CallbackMetaData0 (const std::string &name)
		: ICallbackMetaData (name)
	{}

	void SetFunction (asIScriptFunction *function) { ScriptFunction = function; }
	void ApplyFunction (IComponent *component)
	{
		C *casted_component = dynamic_cast<C*>(component);
		(casted_component->*CallbackPtr)->SetFunction (ScriptFunction);
	}
};

template <class C, class R, class A0, Callback<R(A0)> C::*CallbackPtr>
class CallbackMetaData1 : public ICallbackMetaData <C>
{
public:
	CallbackMetaData1 (const std::string &name)
		: ICallbackMetaData (name)
	{}

	void SetFunction (asIScriptFunction *function) { ScriptFunction = function; }
	void ApplyFunction (IComponent *component)
	{
		C *casted_component = dynamic_cast<C*>(component);
		(casted_component->*CallbackPtr).SetFunction (ScriptFunction);
	}
};

template <class C, class R, class A0, class A1,Callback<R(A0,A1)> C::*CallbackPtr>
class CallbackMetaData2 : public ICallbackMetaData <C>
{
public:
	CallbackMetaData2 (const std::string &name)
		: ICallbackMetaData (name)
	{}

	void SetFunction (asIScriptFunction *function) { ScriptFunction = function; }
	
	void ApplyFunction (IComponent *component)
	{
		C *casted_component = dynamic_cast<C*>(component);
		(casted_component->*CallbackPtr).SetFunction (ScriptFunction);
	}
};

template <class C, class R, class A0, class A1, class A2,Callback<R(A0,A1,A2)> C::*CallbackPtr>
class CallbackMetaData3 : public ICallbackMetaData <C>
{
public:
	CallbackMetaData3 (const std::string &name)
		: ICallbackMetaData (name)
	{}

	void SetFunction (asIScriptFunction *function) { ScriptFunction = function; }
	void ApplyFunction (IComponent *component)
	{
		C *casted_component = dynamic_cast<C*>(component);
		(casted_component->*CallbackPtr).SetFunction (ScriptFunction);
	}
};

}}