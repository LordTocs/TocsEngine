#include "BoundingBox.h"

namespace Tocs {
namespace Math {

BoundingBox EncapsulateTransformedBoundingBox(const BoundingBox &box, const Matrix4 &transform)
{
	Vector3 min(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	Vector3 max(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min());

	for (int i = 0; i < 8; ++i)
	{
		Vector3 transformed = transform * box[i];
		min = std::min(min, transformed);
		max = std::max(max, transformed);
	}

	return BoundingBox::MinMax(min, max);
}

}}