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

Math::Vector3i Voxel::Localize(const Math::Vector3i &vector) const
{
	return GetDirection().Vectori().Dot(vector)   * GetDirection().Vectori()  +
		   GetDirection().Tangenti().Dot(vector)  * GetDirection().Tangenti() +
		   GetDirection().BiNormali().Dot(vector) * GetDirection().BiNormali();
}


Math::Vector3 Voxel::Globalize(const Math::Vector3 &vector) const
{
	return vector.X * GetDirection().Tangent() + vector.Y * GetDirection().Vector() + vector.Z * GetDirection().BiNormal();
}

void Voxel::Set(float fill, Direction direction)
{
	fill = std::min(std::max(fill, 0.0f), 1.0f);
	fill *= 31;
	Info.Fill = static_cast<int>(fill);
	Info.Direction = direction.Index();
}

}}