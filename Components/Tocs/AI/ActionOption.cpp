#include "ActionOption.h"
#include "Mind.h"
#include "Personality.h"
#include <Tocs/Math/Util.h>
#include <cmath>
namespace Tocs{
namespace AI{

PersonalityTarget::PersonalityTarget(const PersonalityAttributeBase &attribute, float target, float width)
: PersonalityAttributeIndex(attribute.Index()), TargetValue(target), RangeSlope(2.0f/width)
{

}

float PersonalityTarget::CalculateInfluence(const Mind &mind)
{
	float personality = mind.Personality.GetAttribute(PersonalityAttributeIndex).Value();
	return Math::Clamp(-std::abs(RangeSlope * (personality - TargetValue)) + 1.0f,-1.0f,1.0f);
}

}
}