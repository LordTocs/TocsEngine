#include "Light.h"
#include "RenderSystem.h"
namespace Tocs {
namespace Rendering {

Light::Light(RenderSystem &system)
: Radius(1), Intensity(1), Color(255,255,255)
{
	system.Add(*this);
}

Light::Light(RenderSystem &system, Math::Vector3 position, float radius, Math::Color color)
: Transform(position), Radius(radius), Color(color), Intensity(1)
{
	system.Add(*this);
}

}}