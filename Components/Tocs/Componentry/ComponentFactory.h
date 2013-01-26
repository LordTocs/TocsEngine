#pragma once
#include <string>
#include <map>
#include <memory>
#include <angelscript.h>

namespace Tocs {
namespace Scripting { class Engine; }
namespace Componentry {

class IComponent;
class Entity;

class IComponentFactory
{
public:
	virtual ~IComponentFactory () {}
	
	virtual IComponent *Get(Entity *entity) = 0;

	virtual void RegisterToEngine (const std::string &type, int internalindex, Scripting::Engine &engine) = 0;
	virtual void ProcessCompiledObject (asIObjectType *object) = 0;
};

template <class C>
class ComponentFactory : public IComponentFactory
{
	std::string Name;
public:
	typedef C ComponentType;
	
	ComponentFactory (const std::string &name)
		: Name(name)
	{}

	IComponent *Get(Entity *entity)
	{
		C *component = new C (entity);
		C::MetaData.ProcessNewComponent(component);
		return static_cast<IComponent *> (component);
	}

	void RegisterToEngine (const std::string &type, int internalindex, Scripting::Engine &engine)
	{
		C::MetaData.RegisterToEngine (type,internalindex,engine);
	}

	void ProcessCompiledObject (asIObjectType *object)
	{
		C::MetaData.ProcessCompiledObject (object);
	}
};

class ComponentRegistry
{
	std::map<std::string,std::unique_ptr<IComponentFactory>> Factories;
public:
	template <class C>
	void RegisterComponent (const std::string &name)
	{
		Factories[name] = std::unique_ptr<IComponentFactory> (new ComponentFactory<C> (name));
	}

	IComponentFactory *GetFactory (const std::string &name)
	{ return Factories[name].get (); }

	static ComponentRegistry &GetRegistry ();
};

}}