#pragma once
#include <Tocs/Math/BoundingBox.h>
#include <Tocs/Graphics/Shader.h>
#include <Tocs/Graphics/ShaderState.h>
#include "DrawCall.h"
namespace Tocs {
namespace Rendering {

class Job
{
public:
	Math::BoundingBox Bounds;
	DrawCall Draw;
	Graphics::ShaderStateSet StateSet;
	unsigned long long SortKey;
	Job(DrawCall call, Graphics::Shader &shader)
	: Draw(call), StateSet(shader) {}

	Job(DrawCall call, Math::BoundingBox bounds, Graphics::Shader &shader)
	: Bounds(bounds), Draw(call), StateSet(shader) {}

	Job(Job &&moveme)
	: Bounds(moveme.Bounds), StateSet(std::move(moveme.StateSet)), Draw(std::move(moveme.Draw)) {}

	Job(const Job &) = delete;
	Job &operator= (const Job &) = delete;

};


}}
