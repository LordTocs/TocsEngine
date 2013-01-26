#pragma once
#include "RenderJob.h"
namespace Tocs {
namespace Rendering {

class PointLight;

class PointLightJob : public RenderJob
{
	PointLight *Light;
public:
	PointLightJob(PointLight *light);
	
	void Render (const Camera &camera, Graphics::GraphicsContext &context);
};

}}
