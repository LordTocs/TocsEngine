#include "Depends.h"

namespace Tocs {
namespace Parallel {


DependantEvents Do (IntermediateEvent &&one)
{
	DependantEvents result;
	result.Add(one);
	return result;
}
DependantEvents Do (IntermediateEvent &&one, IntermediateEvent &&two)
{
	DependantEvents result;
	result.Add(one);
	result.Add(two);
	return result;
}
DependantEvents Do (IntermediateEvent &&one, IntermediateEvent &&two, IntermediateEvent &&three)
{
	DependantEvents result;
	result.Add(one);
	result.Add(two);
	result.Add(three);
	return result;
}

}}