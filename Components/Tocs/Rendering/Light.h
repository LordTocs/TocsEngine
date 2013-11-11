#pragma once
#include "RenderSystem.h"
#include <Tocs/Math/Transform.h>
#include <Tocs/Math/Color.h>
namespace Tocs {
namespace Rendering {

class Light
{
public:
	Math::Transform Transform;
	float Radius;
	Math::Color Color;
	float Intensity;
	
	Light (RenderSystem &system)
		: Radius(1), Intensity(1)
	{}

	Light(RenderSystem &system, Math::Vector3 position, float radius, Math::Color color)
		: Transform(position), Radius(radius), Color(color) {}

};

}}