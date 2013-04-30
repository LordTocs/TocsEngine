#pragma once
#include <list>
#include <Tocs/Graphics/GraphicsContext.h>
#include <Tocs/Graphics/Shader.h>
#include "Camera.h"
namespace Tocs {
namespace Rendering {

class Job;

class Pipe
{
protected:
	std::list<Job *> Jobs;
	virtual void BeginRendering (Graphics::GraphicsContext &context, const Camera &cam) = 0;
	virtual void EndRendering   (Graphics::GraphicsContext &context, const Camera &cam) = 0;
public:
	virtual void ApplyPipeInputs (Graphics::GraphicsContext &context, const Camera &cam, Graphics::Shader &shader) = 0;

	void Render (Graphics::GraphicsContext &context, const Camera &cam);

	void AppendJob (Job &job);
	void RemoveJob (Job &job);
};

}}