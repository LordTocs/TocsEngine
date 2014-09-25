#include "Personality.h"
#include <algorithm>
namespace Tocs {
namespace AI {

PersonalityAttribute::PersonalityAttribute(const PersonalityAttributeBase &base)
: Base(&base), Value_(0.5f) //change to be generated
{

}

/////////////
// Personality Base
/////////////
void PersonalitySetBase::AddAttribute(const std::string &name)
{
	Attributes.emplace_back(name);
}

void PersonalitySetBase::Finalize()
{
	std::sort(Attributes.begin(), Attributes.end(), [](const PersonalityAttributeBase &a, const PersonalityAttributeBase &b){ return a.Name() < b.Name(); });
	for (unsigned int i = 0; i < Attributes.size(); ++i)
	{
		Attributes[i].Index_ = i;
	}
}


int PersonalitySetBase::GetAttributeIndex(const std::string &name) const
{
	auto i = std::lower_bound(Attributes.begin(), Attributes.end(), name, [](const PersonalityAttributeBase &base, const std::string &name){ return base.Name() < name; });
	if (i == Attributes.end())
		return -1;
	if ((*i).Name() != name)
		return -1;
	return i - Attributes.begin();
}
/////////////
// Personality
/////////////
PersonalitySet::PersonalitySet(const PersonalitySetBase &base)
: Base(&base)
{
	for (const auto & attr : base.Attributes)
	{
		Attributes.emplace_back(attr);
	}
}

int PersonalitySet::GetAttributeIndex(const std::string &name) const
{
	return Base->GetAttributeIndex(name);
}

}
}