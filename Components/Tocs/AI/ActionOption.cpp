#include "ActionOption.h"
#include "Mind.h"
#include "Personality.h"
#include <Tocs/Math/Util.h>
#include <cmath>
namespace Tocs{
namespace AI{

InfluenceFunction::InfluenceFunction(float target, float width)
	: TargetValue(target), RangeSlope(2.0f / width)
{

}


float InfluenceFunction::operator()(float value)
{
	return Math::Clamp(-std::abs(RangeSlope * (value - TargetValue)) + 1.0f, -1.0f, 1.0f);
}

}
}