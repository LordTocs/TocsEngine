#pragma once
#include <Tocs/Math/Vector2.h>
#include <Tocs/Math/BoundingBox.h>
#include <vector>

namespace Tocs {
namespace MeshTools {

class PolyLine
{
	std::vector<Math::Vector2> Points;
	Math::BoundingBox2D Bounds;
public:
	void Add (const Math::Vector2 &point);

	const Math::BoundingBox2D &GetBounds () const { return Bounds; }
	const std::vector<Math::Vector2> &GetPoints () const { return Points; }
};

}}

