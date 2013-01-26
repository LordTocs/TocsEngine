#pragma once
#include <Tocs/Math/Color.h>
#include "RenderObject.h"
#include "PointLightJob.h"
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/Shader.h>
namespace Tocs {
namespace Rendering {

class PointLight : public RenderObject
{
	Asset<Graphics::Shader> PointLightShader;
	PointLightJob Job;
	
public:
	friend PointLightJob;

	float Size;
	Math::Color Color;

	PointLight(float size);
	PointLight(float size, const Math::Color &color);
	

	virtual void Update (float dt) {}
};

}}

