#pragma once
#include <string>
#include <map>
#include <Tocs/Graphics/ShaderTypes.h>
//#include "PermutationValue.h"
//#include "PermutationValueSet.h"
#include "PermutationValueType.h"

namespace Tocs {
namespace Rendering {
class ShaderPermutator;
namespace Permutations {

class PermutationValue;
class PermutationValueSet;

class PermutationID
{
public:
	class ValueInfo
	{
	public:
		Permutations::PermutationValueType Type;
		int TextureIndex;
		char Component;
		Graphics::ShaderVariableType VarType;
		bool BinderValue;

		ValueInfo ()
			: Type(Permutations::PermutationValueType::Constant), TextureIndex(-1), Component('x'), VarType(Graphics::ShaderVariableType::Int), BinderValue(false)
		{
		}

		ValueInfo (const Graphics::ShaderVariableType &vartype)
			: Type(Permutations::PermutationValueType::None), TextureIndex(-1), Component('x'), VarType(vartype), BinderValue(false)
		{
		}

		bool operator< (const ValueInfo &op2) const;
		
	};
private:
	unsigned int TextureCount;
	std::map<std::string, ValueInfo> ValueTypes; 
public:
	PermutationID (ShaderPermutator &permutator, PermutationValueSet &values);
	bool operator< (const PermutationID &op2) const;

	ValueInfo &operator[] (const std::string &name)
	{ return ValueTypes[name]; }
	const ValueInfo &operator[] (const std::string &name) const 
	{ return (*ValueTypes.find (name)).second; }

	unsigned int GetTextureCount () const { return TextureCount; }

	
};

}}}