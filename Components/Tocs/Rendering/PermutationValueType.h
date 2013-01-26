#pragma once
#include <string>
namespace Tocs {
namespace Rendering {
namespace Permutations {

class PermutationValueType
{
	enum InternalFormat
	{
		constant,
		map,
		mapcomponent,
		none
	};
	InternalFormat Internal;

	PermutationValueType (InternalFormat format)
		: Internal (format) {}

public:
	const static PermutationValueType Constant;
	const static PermutationValueType Map;
	const static PermutationValueType MapComponent;
	const static PermutationValueType None;

	PermutationValueType()
		: Internal(none)
	{}

	bool operator ==  (const PermutationValueType &op2) const {return Internal == op2.Internal;}
	bool operator !=  (const PermutationValueType &op2) const {return Internal != op2.Internal;}
	bool operator <   (const PermutationValueType &op2) const {return Internal < op2.Internal;}

	static PermutationValueType FromString(std::string name);
};


}}}