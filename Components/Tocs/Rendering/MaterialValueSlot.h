#pragma once
#include <Tocs/Graphics/ShaderTypes.h>
namespace Tocs {
namespace Rendering {

//Designates type, and corripsonds to shader template variable.
class MaterialValueSlot
{
	Graphics::ShaderVariableType VariableType;
	const std::string VariableName;
	unsigned int VariableIndex;
public:
	MaterialValueSlot(const std::string &name, const Graphics::ShaderVariableType &type, unsigned int index)
		: VariableType (type), VariableName (name), VariableIndex(index)
	{
	}

	const std::string &Name () const { return VariableName; }
	const Graphics::ShaderVariableType &Type () const { return VariableType; }
	unsigned int Index () const { return VariableIndex; }


};

}}