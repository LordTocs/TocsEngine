#include "Voxel.h"

namespace Tocs {
namespace Voxels {

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

void Voxel::Set(unsigned char fill, Direction direction)
{
	Info.Fill = std::min<unsigned char>(std::max<unsigned char>(fill, 0), 31);
	Info.Direction = direction.Index();
}

}}