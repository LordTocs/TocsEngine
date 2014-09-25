#pragma once
#include "Need.h"
#include "Personality.h"
#include "Relationship.h"
namespace Tocs {
namespace AI {

class MindBase
{
public:
	PersonalitySetBase Personality;
	NeedSetBase Needs;
};

class Mind
{
public:
	Mind(const MindBase &base);

	PersonalitySet Personality;
	NeedSet Needs;
	RelationshipSet Relationships;

	unsigned int CalculateMemoryUsage();
};

}
}

