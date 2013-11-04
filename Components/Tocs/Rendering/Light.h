#pragma once
#include "RenderSystem.h"
#include <Tocs/Math/Transform.h>

namespace Tocs {
namespace Rendering {

class Light
{
public:
	Math::Transform Transform;
	float Radius;
	
	Light (RenderSystem &system)
	{}

};

}}