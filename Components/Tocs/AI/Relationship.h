#pragma once
#include <map>
namespace Tocs {
namespace AI {
class Mind;

class Relationship
{
	Mind *Other;
	float BaseQuality_;
	//[0,1]
	float Familiarity_;
public:
	Relationship(Mind &other);
	 
	const float &Quality() const { return BaseQuality_; }
	const float &Familiarity() const { return Familiarity_; }

	void OffsetQuality(float delta) { BaseQuality_ += delta; }

};

class RelationshipSet
{
	std::map<const Mind *, Relationship> Relationships;
public:
	
	void AddRelationship(Mind &other);

	const Relationship &GetRelationship(const Mind &other) const;
	Relationship &GetRelationship(const Mind &other);
};

}
}


