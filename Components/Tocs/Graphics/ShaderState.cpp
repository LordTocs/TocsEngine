#include "ShaderState.h"
#include <cassert>
namespace Tocs {
namespace Graphics {

ShaderState::ShaderState()
{

}

ShaderState::ShaderStateValue &ShaderState::operator[](const std::string &uniformname)
{
	auto i = std::find_if(Values.begin(), Values.end(), [&](const ShaderStateValue& value) { return value.Name() == uniformname; });
	if (i == Values.end())
	{
		assert(false && "shaderstate not found");
	}
	return *i;
}

const ShaderState::ShaderStateValue &ShaderState::operator[](const std::string &uniformname) const
{
	auto i = std::find_if(Values.begin(), Values.end(), [&](const ShaderStateValue& value) { return value.Name() == uniformname; });
	if (i == Values.end())
	{
		assert(false && "shaderstate not found");
	}
	return *i;
}

void ShaderState::AddValue(const std::string &name)
{
	Values.emplace_back(name);
}

ShaderStateMapping::Mapping::Mapping(Shader &shader, const ShaderState &state)
: State(&state)
{
	for (int i = 0; i < state.ValueCount(); ++i)
	{
		Uniforms.push_back(shader[state[i].Name()]);
	}
}

void ShaderStateMapping::Mapping::Bind()
{
	for (int i = 0; i < State->ValueCount(); ++i)
	{
		(*State)[i].Bind(Uniforms[i]);
	}
}

}}