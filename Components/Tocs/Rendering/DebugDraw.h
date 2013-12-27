#pragma once
#include <vector>
#include <Tocs/Math/Color.h>
#include <Tocs/Math/Vector.h>
#include <Tocs/Math/BoundingBox.h>
#include <Tocs/Graphics/GraphicsContext.h>
#include "Camera.h"
namespace Tocs {
namespace Rendering {

class DebugDraw
{
	class Segment
	{
	public:
		Math::Vector3 a;
		Math::Vector3 b;
		Math::Color color;
		Segment(Math::Vector3 a, Math::Vector3 b, Math::Color color)
			: a(a), b(b), color(color) {}
	};
	static std::vector<Segment> Lines;
public:
	DebugDraw() = delete;
	DebugDraw(const DebugDraw &) = delete;

	static void Line(const Math::Vector3 &a, const Math::Vector3 &b);
	static void Line(const Math::Vector3 &a, const Math::Vector3 &b, Math::Color color);

	static void Draw(Graphics::GraphicsContext &context, const Camera &cam);

	static void Clear();
};

}}