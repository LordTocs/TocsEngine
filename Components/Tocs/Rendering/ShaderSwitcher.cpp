#include "ShaderSwitcher.h"

namespace Tocs {
namespace Rendering {



void ShaderSwitcher::ResetFrame()
{
	/*std::vector<TopStateData> topstates;
	topstates.reserve(StateUsages.size());

	for (auto i : StateUsages)
	{
	auto rankedstatei = std::lower_bound(topstates.begin(), topstates.end(), i.second.UsageCount, [](const TopStateData &a, const int &b) { return a.UsageCount > b; });
	topstates.insert(rankedstatei, TopStateData(i.first,&i.second));
	i.second.UsageCount = 0;
	i.second.CommonIndex = -1;
	}

	for (int i = 0; i < MaxTrackedStates && i < topstates.size(); ++i)
	{
	StateUsages[topstates[i].State].CommonIndex = i;
	}
	*/


	CurrentShader = nullptr;
}

void ShaderSwitcher::SwitchStateSet(Graphics::ShaderStateSet &set)
{
	++BindIndex;
	if (CurrentShader != &set.GetShader())
	{
		++BindIndex; //Force all states to rebind.
		if (CurrentShader != nullptr)
			CurrentShader->UnBind();

		CurrentShader = &set.GetShader();
		CurrentShader->Bind();
	}
	/*
	for (int i = 0; i < set.MappingCount(); ++i)
	{
		Graphics::ShaderStateMapping &state = set.GetMapping(i);
		Graphics::ShaderStateUsage &usage = const_cast<Graphics::ShaderStateUsage &> (state.GetState().GetUsage(UsageIndex));
		++usage.UsageCount;

		if (usage.LastBindIndex == BindIndex - 1)
		{
			usage.LastBindIndex = BindIndex;
			continue; //State is already bound.
		}
		state.Bind();
		usage.LastBindIndex = BindIndex;
	}*/
	
	for (int i = 0; i < set.MappingCount(); ++i)
	{
		Graphics::ShaderStateMapping &state = set.GetMapping(i);
		state.Bind();
	}
}

unsigned int ShaderSwitcher::GetCommonStateBitfield(Graphics::ShaderStateSet &set)
{
	unsigned int result = 0;
	for (auto i : set)
	{
		const Graphics::ShaderStateUsage &usage = i.GetState().GetUsage(UsageIndex);
		if (usage.CommonIndex != -1)
		{
			result |= 1 >> usage.CommonIndex;
		}
	}
	return result;
}

}
}
