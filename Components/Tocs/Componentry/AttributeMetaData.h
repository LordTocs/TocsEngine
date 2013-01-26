#pragma once
#include <string>
#include <memory>
#include "Attribute.h"
#include "Entity.h"

namespace Tocs {

namespace Scripting { class Engine; }

namespace Componentry {

template <class C>
class IAttributeMetaData
{
protected:
	std::string Name;
public:
	IAttributeMetaData (const std::string &name)
		: Name (name)
	{}

	virtual ~IAttributeMetaData () {}

	virtual void RegisterToEngine (const std::string &type, Scripting::Engine &engine) {}
};

template <class C,class T, Attribute<T> C::*AttrPtr>
class AttributeMetaData : public IAttributeMetaData<C>
{
public:
	AttributeMetaData (const std::string &name)
		: IAttributeMetaData(name)
	{}

	static T GetFunc (Entity *ent)
	{
		return (ent->GetComponent<C> ()->*AttrPtr);
	}

	static void SetFunc(T t, Entity *ent)
	{
		(ent->GetComponent<C> ()->*AttrPtr) = t;
	}

	void RegisterToEngine (const std::string &type, Scripting::Engine &engine) 
	{
		std::stringstream ss;
		ss << Scripting::GetTypeString<T> () << " get_" << Name << " (" << type << "@)";
		int r = engine.GetEnginePtr()->RegisterObjectMethod(type.c_str(), (ss.str()).c_str() , asFUNCTION(GetFunc),asCALL_CDECL_OBJLAST);
		ss.str("");
		ss << "void set_" << Name << " (" << Scripting::GetTypeString<T> () << ", " << type << "@)";
		    r = engine.GetEnginePtr()->RegisterObjectMethod(type.c_str(), (ss.str()).c_str(), asFUNCTION(SetFunc),asCALL_CDECL_OBJLAST);
	}
};

}}