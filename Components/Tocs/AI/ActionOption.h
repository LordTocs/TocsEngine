#pragma once
#include <string>
namespace Tocs {
namespace AI {

class Mind;
class PersonalityAttributeBase;

class InfluenceFunction
{
	float TargetValue;
	float RangeSlope;
public:
	InfluenceFunction(float target, float width);

	float operator()(float value);
};

//Action slot?
//Weighting

class ActionWeighting
{

};


}
}

