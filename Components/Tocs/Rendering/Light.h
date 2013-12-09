#pragma once
#include <Tocs/Math/Transform.h>
#include <Tocs/Math/Color.h>
namespace Tocs {
namespace Rendering {

class RenderSystem;

class Light
{
public:
	Math::Transform Transform;
	float Radius;
	Math::Color Color;
	float Intensity;
	
	Light(RenderSystem &system);
	Light(RenderSystem &system, Math::Vector3 position, float radius, Math::Color color);

};

}}