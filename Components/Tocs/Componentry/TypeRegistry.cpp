#include "TypeRegistry.h"
#include "Entity.h"
#include "World.h"
#include <iostream>

using namespace std;

namespace Tocs {
namespace Componentry {

void TypeRegistry::LoadFile (const std::string &filename)
{
	std::unique_ptr<EntityType> type(new EntityType(filename, WorldPtr.GetEngine()));
	if (TypeMap.find(type->GetName()) != TypeMap.end ())
	{
		cout << "Already found type " << type->GetName () << " in typemap." << endl;
		return;
	}
	TypeMap.emplace(type->GetName(),std::move(type));
}

Entity *TypeRegistry::Create (const std::string &type)
{
	auto i = TypeMap.find (type);

	if (i == TypeMap.end ())
		return nullptr;

	return new Entity ((*i).second.get(),WorldPtr);
}

}}