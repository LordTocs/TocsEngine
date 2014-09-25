#include "Need.h"
#include <algorithm>
namespace Tocs {
namespace AI {

Need::Need(const NeedBase &base)
	: Base(&base), Value_(0.5f) //change to be generated
{

}

/////////////
// NeedSet Base
/////////////
void NeedSetBase::AddNeed(const std::string &name)
{
	Needs.emplace_back(name);
}

void NeedSetBase::Finalize()
{
	std::sort(Needs.begin(), Needs.end(), [](const NeedBase &a, const NeedBase &b){ return a.Name() < b.Name(); });
	for (unsigned int i = 0; i < Needs.size(); ++i)
	{
		Needs[i].Index_ = i;
	}
}


int NeedSetBase::GetNeedIndex(const std::string &name) const
{
	auto i = std::lower_bound(Needs.begin(), Needs.end(), name, [](const NeedBase &base, const std::string &name){ return base.Name() < name; });
	if (i == Needs.end())
		return -1;
	if ((*i).Name() != name)
		return -1;
	return i - Needs.begin();
}
/////////////
// NeedSet
/////////////
NeedSet::NeedSet(const NeedSetBase &base)
	: Base(&base)
{
	for (const auto & need : base.Needs)
	{
		Needs.emplace_back(need);
	}
}

int NeedSet::GetNeedIndex(const std::string &name) const
{
	return Base->GetNeedIndex(name);
}

}
}