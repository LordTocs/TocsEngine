#pragma once
#include <Tocs/Math/BoundingBox.h>
#include <Tocs/Graphics/Shader.h>
#include <Tocs/Graphics/ShaderInput.h>
#include "DrawCall.h"
namespace Tocs {
namespace Rendering {

class Job
{
public:
	Math::BoundingBox Bounds;
	DrawCall Draw;
	Graphics::Shader *DrawShader;
	Graphics::ShaderInput Input;
	Job(DrawCall call, Graphics::Shader &shader)
	: Draw(call), DrawShader(&shader), Input(shader) {}

	Job(DrawCall call, Math::BoundingBox bounds, Graphics::Shader &shader)
	: Bounds(bounds), Draw(call), DrawShader(&shader), Input(shader) {}

	Job(Job &&moveme)
	: Bounds(moveme.Bounds), DrawShader(moveme.DrawShader), Draw(std::move(moveme.Draw)), Input(std::move(moveme.Input)) {}

	Job(const Job &) = delete;
	Job &operator= (const Job &) = delete;

};


}}
