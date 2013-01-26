#include "PermutationValueType.h"

namespace Tocs {
namespace Rendering {
namespace Permutations {

const PermutationValueType PermutationValueType::Constant(constant);
const PermutationValueType PermutationValueType::Map(map);
const PermutationValueType PermutationValueType::MapComponent(mapcomponent);
const PermutationValueType PermutationValueType::None(none);

PermutationValueType PermutationValueType::FromString (std::string name)
{
	if (name == "Constant")
		return Constant;
	if (name == "Map")
		return Map;
	if (name == "MapComponent")
		return MapComponent;
	return None;
}

}}}