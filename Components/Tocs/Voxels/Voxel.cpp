#include "Voxel.h"

namespace Tocs {
namespace Voxels {

FaceType Voxel::GetFaceState (Direction direction) const
{
	if (IsEmpty ())
		return FaceType::NoFill;
	if (IsFilled())
		return FaceType::Filled;

	if (direction == GetDirection())
	{
		return FaceType::Augmented;
	}

	if (direction == GetDirection().Opposite())
	{
		return FaceType::Filled;
	}

	return FaceType::NoFill;
}

}}