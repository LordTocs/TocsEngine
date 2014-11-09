#include "ShaderState.h"
#include <cassert>
namespace Tocs {
namespace Graphics {
	 

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

ShaderState::ShaderStateValue &ShaderState::AddValue(const std::string &name)
{
	auto i = std::lower_bound(Values.begin(), Values.end(), name, [](const ShaderStateValue &value, const std::string &n) { return value.Name() < n; });
	return *Values.emplace(i,name);
}

bool ShaderState::HasValue(const std::string &uniformname) const
{
	auto i = std::find_if(Values.begin(), Values.end(), [&](const ShaderStateValue& value) { return value.Name() == uniformname; });
	return i != Values.end();
}


ShaderStateMapping::ShaderStateMapping(Shader &shader, const ShaderState &state)
: MappedShader(&shader)
, State(&state)
{
	for (int i = 0; i < state.ValueCount(); ++i)
	{
		Uniforms.push_back(shader[state[i].Name()]);
	}
}

void ShaderStateMapping::Bind()
{
	for (int i = 0; i < State->ValueCount(); ++i)
	{
		(*State)[i].Bind(Uniforms[i]);
	}
}

void ShaderStateSet::MapState(const ShaderState &state)
{
	Mappings.emplace_back(*MappedShader, state);
}

void ShaderStateSet::BindAll()
{
	for (auto i : Mappings)
	{
		i.Bind();
	}
}

}}