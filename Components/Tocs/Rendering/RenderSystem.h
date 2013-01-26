#pragma once
#include "Pipeline.h"

namespace Tocs {
namespace Rendering {

class RenderObject;

class RenderSystem
{
	Pipeline Pipes;
public:
	RenderSystem();
	~RenderSystem();

	void AddObject (RenderObject &object);

	Pipeline &GetPipes () { return Pipes; }

	void Render (const Camera &cam, Graphics::GraphicsContext &context);
};

}}