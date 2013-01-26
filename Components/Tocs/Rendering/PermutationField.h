#pragma once
#include <string>
#include <Tocs/Graphics/ShaderTypes.h>

namespace Tocs {
namespace Rendering {
namespace Permutations {


class PermutationField
{
	Graphics::ShaderVariableType Type;
	std::string Name;
public:
	PermutationField ()
		: Type(Graphics::ShaderVariableType::Int)
	{
	}

	PermutationField(const std::string &name, const Graphics::ShaderVariableType &type)
		: Type(type), Name(name)
	{}

	Graphics::ShaderVariableType GetType () const { return Type; }
	const std::string &GetName () const { return Name; }
};

}}}