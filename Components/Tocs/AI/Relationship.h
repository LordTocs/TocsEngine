#pragma once
#include <vector>
namespace Tocs {
namespace AI {
class Mind;

class Relationship
{
	Mind *Other_;
	float BaseQuality_;
	//[0,1]
	float Familiarity_;
public:
	Relationship(Mind &other);
	 
	const float &Quality() const { return BaseQuality_; }
	const float &Familiarity() const { return Familiarity_; }

	void OffsetQuality(float delta) { BaseQuality_ += delta; }

	Mind &Other() { return *Other_; }
	const Mind &Other() const { return *Other_; }

};

class RelationshipSet
{
	std::vector<Relationship> Relationships;
public:
	
	void AddRelationship(Mind &other);

	const Relationship &GetRelationship(const Mind &other) const;
	Relationship &GetRelationship(const Mind &other);
};

}
}


