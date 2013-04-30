#pragma once
#include "Job.h"
#include "RenderObject.h"
#include "StaticGeometry.h"
#include "BasicShading.h"
#include "LightHulls.h"
#include <Tocs/Math/Color.h>
namespace Tocs {
namespace Rendering {

class PointLight : public RenderObject
{
	StaticGeometry LightGeometry;
	Asset<BasicShadingType> LightShadingType;
	BasicShading LightShading;
	Job DeferredJob;
protected:
	void QueueJobs ();
	void DequeueJobs ();
public:
	Math::Color Color;
	float Intensity;
	float Radius;
	PointLight(RenderSystem &system);
	void Update(float dt);
};

}}