#pragma once
#include <string>
namespace Tocs {
namespace AI {

class Mind;
class PersonalityAttributeBase;

class PersonalityTarget
{
	unsigned int PersonalityAttributeIndex;
	float TargetValue;
	float RangeSlope;
public:
	PersonalityTarget(const PersonalityAttributeBase &attribute, float target, float width);

	float CalculateInfluence(const Mind &mind);

};
//Forms a "template" for encapsulating parameters to select an action
class ActionOptionBase
{
public:
	
};

class ActionOption
{
public:
	
};

}
}

