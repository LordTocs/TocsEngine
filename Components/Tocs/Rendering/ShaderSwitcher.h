#pragma once
#include <Tocs/Graphics/ShaderState.h>

#include <unordered_map>
#include <vector>
namespace Tocs {
namespace Rendering {



class ShaderSwitcher
{
	Graphics::Shader *CurrentShader;
	int BindIndex;
	int MaxTrackedStates;
	int UsageIndex;
public:
	ShaderSwitcher(int trackedstates, int usageindex)
		: CurrentShader(nullptr)
		, BindIndex(0)
		, MaxTrackedStates(trackedstates)
		, UsageIndex(usageindex)
	{}

	void ResetFrame();

	void SwitchStateSet(Graphics::ShaderStateSet &set);

	unsigned int GetCommonStateBitfield(Graphics::ShaderStateSet &set);

};

}}

