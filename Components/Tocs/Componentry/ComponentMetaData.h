#pragma once
#include <string>
#include <set>
#include <memory>
#include <functional>
#include <iostream>
#include "AttributeMetaData.h"
#include "MethodMetaData.h"
#include "CallbackMetaData.h"

namespace Tocs {
namespace Componentry {

template <class T>
class HasInitType
{
	typedef int yes;
	typedef char no;
                  
    template <typename C> static yes &chk(decltype (&C::InitType)); \
    template <typename>   static no  &chk(...);
public:
	static bool const value = (sizeof(chk<T>(0)) == sizeof(yes));
};

template <class C>
class GenMetaData
{
public:
	template <class T>
	class Attribute
	{
	public:
		template <Componentry::Attribute<T> C::*Attr>
		static IAttributeMetaData<C> *Get (const std::string &name)
		{
			return new AttributeMetaData<C,T,Attr> (name);
		}
	};

	template <class>
	class Method;

	template <class R>
	class Method <R()>
	{
	public:
		template <R (C::*__thiscall FuncPtr)()>
		static IMethodMetaData<C> *Get (const std::string &name)
		{
			return new MethodMetaData0<C, R, FuncPtr> (name);
		}
	};

	template <class R, class A0>
	class Method <R(A0)>
	{
	public:
		template <R (C::*__thiscall FuncPtr)(A0)>
		static IMethodMetaData<C> *Get (const std::string &name)
		{
			return new MethodMetaData1<C,R,A0, FuncPtr> (name);
		}
	};


	template <class>
	class Callback;

	template <class R>
	class Callback <R()>
	{
	public:
		template <Componentry::Callback<R()> C::*Attr>
		static ICallbackMetaData<C> *Get (const std::string &name)
		{
			return new CallbackMetaData0<C,R,Attr> (name);
		}
	};

	template <class R, class A0>
	class Callback <R(A0)>
	{
	public:
		template <Componentry::Callback<R(A0)> C::*Attr>
		static ICallbackMetaData<C> *Get (const std::string &name)
		{
			return new CallbackMetaData1<C,R,A0,Attr> (name);
		}
	};
};



template <class C>
class ComponentMetaData
{
	std::set <std::unique_ptr <IAttributeMetaData<C>>> Attributes;
	std::set <std::unique_ptr <IMethodMetaData<C>>> Methods;
	std::set <std::unique_ptr <ICallbackMetaData<C>>> Callbacks;
public:
	ComponentMetaData ()
	{	
		static_assert (HasInitType<C>::value, "Components must define a static InitType function to initialize the meta data.");
		std::string typen = C::InitType();
		ComponentRegistry::GetRegistry ().RegisterComponent <C> (typen);
		std::cout << "Registering component: " << typen << std::endl;
	}

	void RegisterToEngine (const std::string &type, int internalindex, Scripting::Engine &engine)
	{
		for (auto i = Attributes.begin(); i != Attributes.end(); ++i)
		{
			(*i).get()->RegisterToEngine (type,engine);
		}
		for (auto i = Methods.begin(); i != Methods.end(); ++i)
		{
			(*i).get()->RegisterToEngine (type,internalindex,engine);
		}
	}

	void ProcessCompiledObject (asIObjectType *object)
	{
		for (auto i = Callbacks.begin(); i != Callbacks.end (); ++i)
		{
			asIScriptFunction *func = object->GetMethodByName((*i)->GetName ().c_str());
			if (func != nullptr)
			{
				(*i)->SetFunction(func);
			}
		}
	}

	void ProcessNewComponent (C *component)
	{
		for (auto i = Callbacks.begin(); i != Callbacks.end (); ++i)
		{
			(*i).get()->ApplyFunction(component);
		}
	}

	void Add (IAttributeMetaData<C> *attribute)
	{ 
		Attributes.insert (std::unique_ptr<IAttributeMetaData<C>> (attribute)); 
	}
	void Add (IMethodMetaData<C> *method)
	{
		Methods.insert (std::unique_ptr<IMethodMetaData<C>>(method));
	}
	void Add (ICallbackMetaData<C> *callback)
	{
		Callbacks.insert(std::unique_ptr<ICallbackMetaData<C>>(callback));
	}
};

}}