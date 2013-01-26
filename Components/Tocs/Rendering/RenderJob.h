#pragma once
#include <list>
#include "Camera.h"
#include <Tocs/Graphics/GraphicsContext.h>
#include <Tocs/Math/Transform.h>
#include <Tocs/Graphics/Shader.h>
namespace Tocs {
namespace Rendering {

class Pipe;
class Pipeline;

class RenderJob
{
	std::list<RenderJob *>::iterator Iterator;
	void Remove ();
protected:
	Pipe *OwnerPipe;
	Math::Transform &Transformation;
	bool Visible;
	Graphics::Shader &JobShader;
public:
	friend class Pipe;

	RenderJob(Math::Transform &transform, Graphics::Shader &shader)
		: OwnerPipe (nullptr), Transformation(transform), Visible(true), JobShader(shader) {}
	virtual ~RenderJob();
	virtual void Render (const Camera &camera, Graphics::GraphicsContext &context) = 0;
	virtual bool IsVisible (const Camera &) const { return Visible; }

	void Show () { Visible = true; }
	void Hide () { Visible = false; }
};

}}