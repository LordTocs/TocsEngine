#pragma once
#include <Tocs/Math/BoundingBox.h>
namespace Tocs {
namespace Rendering {

class MeshPart
{
	unsigned int Offset;
	unsigned int Length;
	Math::BoundingBox Bounds;
public:
	MeshPart (unsigned int offset, unsigned int length)
		: Offset(offset), Length(length)
	{}
	MeshPart(unsigned int offset, unsigned int length, Math::BoundingBox bounds)
	: Offset(offset), Length(length), Bounds(bounds) {}

	unsigned int GetOffset () const { return Offset; }
	unsigned int GetLength () const { return Length; }
	const Math::BoundingBox &GetBounds() const { return Bounds; }
	Math::BoundingBox &GetBounds() { return Bounds; }
};


}}
