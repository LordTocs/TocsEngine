#pragma once
#include <string>
#include <map>
#include <memory>
#include "EntityType.h"

namespace Tocs {
namespace Componentry {

class World;

class TypeRegistry
{
	std::map<std::string, std::unique_ptr<EntityType>> TypeMap;
	World &WorldPtr;
public:
	TypeRegistry(World &world)
		: WorldPtr (world)
	{}

	~TypeRegistry()
	{
	}

	void LoadFile (const std::string &filename);

	Entity *Create (const std::string &type);
};

}}