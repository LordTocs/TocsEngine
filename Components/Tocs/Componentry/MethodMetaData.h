#pragma once
#include <string>
#include <memory>
#include "Entity.h"
#include <Tocs/Scripting/TypeStrings.h>

namespace Tocs {
namespace Componentry {

template <class C>
class IMethodMetaData
{
protected:
	std::string Name;
public:
	IMethodMetaData (const std::string &name)
		: Name(name)
	{}

	virtual ~IMethodMetaData () {}

	virtual void RegisterToEngine (const std::string &type, int internalindex, Scripting::Engine &engine) {}
};




template <class C, class R, R (C::*FuncPtr) ()>
class MethodMetaData0 : public IMethodMetaData <C>
{
	R (C::*FuncPtr) ();
public:
	MethodMetaData0 (const std::string &name)
		: IMethodMetaData(name)
	{}

	static R Invoke (Entity *ent)
	{
		return (ent->GetComponent<C> ()->*FuncPtr) ();
	}

	void RegisterToEngine (const std::string &type, int internalindex, Scripting::Engine &engine) 
	{
		int r = engine.GetEnginePtr ()->RegisterObjectMethod (type.c_str (),Scripting::GetFunctionString(FuncPtr,Name).c_str(),asFUNCTION(Invoke),asCALL_CDECL_OBJLAST);
	}
};



template <class C, class R, class A0, R (C::*__thiscall FuncPtr) (A0)>
class MethodMetaData1 : public IMethodMetaData <C>
{
public:
	MethodMetaData1 (const std::string &name)
		: IMethodMetaData(name)
	{}

	static R Invoke (A0 a0, Entity *ent)
	{ 
		return (ent->GetComponent<C> ()->*FuncPtr) (a0); 
	}

	void RegisterToEngine (const std::string &type, int internalindex, Scripting::Engine &engine) 
	{
		int r = engine.GetEnginePtr ()->RegisterObjectMethod (type.c_str (),Scripting::GetFunctionString(FuncPtr,Name).c_str(),asFUNCTION(Invoke),asCALL_CDECL_OBJLAST);
	}
};


/*
template <class,class A, A a>
class MethodMetaData;

template <class, class>
class Method;
/*
template <class C, class R>
class MethodMetaData<C,R()> : public IMethodMetaData <C>
{
	R (C::*FuncPtr) ();
public:
	MethodMetaData (const std::string &name, R (C::*func) ())
		: IMethodMetaData(name),
		  FuncPtr (func)
	{}

	static R Invoke (Entity *ent)
	{
		return (ent->GetComponent<C> ()->*FuncPtr) ();
	}

	void RegisterToEngine (const std::string &type, int internalindex, Scripting::Engine &engine) 
	{
		int r = engine.GetEnginePtr ()->RegisterObjectMethod (type.c_str (),"",asFUNCTION(Invoke),asCALL_CDECL_OBJLAST);
	}
};

template <class C, class R, class A0,R C::*FuncPtr (A0)>
class MethodMetaData<C,R(A0),FuncPtr> : public IMethodMetaData <C>
{
public:
	MethodMetaData (const std::string &name)
		: IMethodMetaData(name)
	{}

	static R Invoke (A0 a0, Entity *ent);
	//{ return (ent->GetComponent<C> ()->*FuncPtr) (a0); }

	void RegisterToEngine (const std::string &type, int internalindex, Scripting::Engine &engine) 
	{
		int r = engine.GetEnginePtr ()->RegisterObjectMethod (type.c_str (),"",asFUNCTION(Invoke),asCALL_CDECL_OBJLAST);
	}
};

/*
template <class C, class R, class A0, class A1>
class MethodMetaData<C,R(A0,A1)> : public IMethodMetaData <C>
{
	R (C::*FuncPtr) (A0,A1);
public:
	MethodMetaData (const std::string &name, R (C::*func) (A0,A1))
		: IMethodMetaData(name),
		  FuncPtr (func)
	{}

	static R Invoke (A0 a0, A1 a1, Entity *ent)
	{
		return (ent->GetComponent<C> ()->*FuncPtr) (a0,a1);
	}

	void RegisterToEngine (const std::string &type, int internalindex, Scripting::Engine &engine) 
	{
		int r = engine.GetEnginePtr ()->RegisterObjectMethod (type.c_str (),"",asFUNCTION(Invoke),asCALL_CDECL_OBJLAST);
	}

};

template <class C, class R, class A0, class A1,class A2>
class MethodMetaData<C,R(A0,A1,A2)> : public IMethodMetaData <C>
{
	R (C::*FuncPtr) (A0,A1,A2);
public:
	MethodMetaData (const std::string &name, R (C::*func) (A0,A1,A2))
		: IMethodMetaData(name),
		  FuncPtr (func)
	{}
	static R Invoke (A0 a0, A1 a1, A2 a2, Entity *ent)
	{
		return (ent->GetComponent<C> ()->*FuncPtr) (a0,a1,a2);
	}

	void RegisterToEngine (const std::string &type, int internalindex, Scripting::Engine &engine) 
	{
		int r = engine.GetEnginePtr ()->RegisterObjectMethod (type.c_str (),"",asFUNCTION(Invoke),asCALL_CDECL_OBJLAST);
	}
};
*/


}}