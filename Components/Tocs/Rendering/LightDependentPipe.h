#pragma once
#include <list>
#include <Tocs/Graphics/GraphicsContext.h>
#include <Tocs/Graphics/Shader.h>
#include "Camera.h"
#include "Light.h"
namespace Tocs {
namespace Rendering {

class LightDependentJob;

class LightDependentPipe
{
protected:
	std::list<LightDependentJob *> Jobs;
	virtual void BeginRendering (Graphics::GraphicsContext &context, const Camera &cam) = 0;
	virtual void EndRendering   (Graphics::GraphicsContext &context, const Camera &cam) = 0;
public:
	virtual void ApplyPipeInputs (Graphics::GraphicsContext &context, const Camera &cam, Graphics::Shader &shader) = 0;

	void Render (Graphics::GraphicsContext &context, const Camera &cam, Light &light);

	void AppendJob (LightDependentJob &job);
	void RemoveJob (LightDependentJob &job);
};

}}