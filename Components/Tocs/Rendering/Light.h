#pragma once
#include <Tocs/Math/Transform.h>
#include <Tocs/Math/Color.h>
#include <Tocs/Math/BoundingBox.h>
#include "Camera.h"

namespace Tocs {
namespace Rendering {

class RenderSystem;

class Light
{
	RenderSystem &System;
	Math::BoundingBox2Di ScreenRect;
	int ShadowIndex;
public:
	Math::Transform Transform;
	float Radius;
	Math::Color Color;
	float Intensity;
	bool Shadows;


	
	Light(RenderSystem &system);
	Light(RenderSystem &system, Math::Vector3 position, float radius, Math::Color color);
	~Light();

	Light(const Light &) = delete;
	Light &operator= (const Light &) = delete;

	void ComputeScreenRect(const Camera &cam);
	int ScreenSpace() const { return ScreenRect.Width() * ScreenRect.Height(); }

	bool Visible() const;

	void ShadowMap(int index) { ShadowIndex = index; }
	int ShadowMap() const { return ShadowIndex; }

};

}}