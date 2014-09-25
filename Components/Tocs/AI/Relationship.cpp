#include "Relationship.h"


namespace Tocs {
namespace AI{

Relationship::Relationship(Mind &other)
: Other(&other), BaseQuality_(0.0f), Familiarity_(0.0f)
{

}

void RelationshipSet::AddRelationship(Mind &other)
{
	Relationships.emplace(&other,other);
}

const Relationship &RelationshipSet::GetRelationship(const Mind &other) const
{
	auto i = Relationships.find(&other);
	return (*i).second;
}

}
}