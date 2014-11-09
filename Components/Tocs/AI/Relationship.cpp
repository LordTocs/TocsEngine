#include "Relationship.h"
#include <algorithm>

namespace Tocs {
namespace AI{

Relationship::Relationship(Mind &other)
: Other_(&other), BaseQuality_(0.0f), Familiarity_(0.0f)
{

}

void RelationshipSet::AddRelationship(Mind &other)
{
	auto i = std::lower_bound(Relationships.begin(), Relationships.end(), &other, [](const Relationship &a, const Mind *b) { return &(a.Other()) < b; });
	Relationships.emplace(i,other);
}

const Relationship &RelationshipSet::GetRelationship(const Mind &other) const
{
	auto i = std::lower_bound(Relationships.begin(), Relationships.end(), &other, [](const Relationship &a, const Mind *b) { return &(a.Other()) < b; });
	if (i == Relationships.end())
	{
		//ERRROR
	}
	return *i;
}

}
}