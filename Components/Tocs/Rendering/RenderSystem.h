#pragma once
#include <vector>
#include "Camera.h"
#include "Pipeline.h"
namespace Tocs {
namespace Rendering {

class RenderObject;

//Holds all objects in the scene, handles rendering and updating
class RenderSystem
{
	RenderSystem (const RenderSystem &); //no copying...
	RenderSystem &operator= (const RenderSystem &);
	//Replace with better scene container.
	std::vector<RenderObject *> Objects;
	
public:
	Pipeline Pipes;

	friend class RenderObject;
	RenderSystem(Graphics::GraphicsContext &context);
	void Update (float dt);
	void Render (Graphics::GraphicsContext &context, const Camera &camera);

	void AddObject (RenderObject &);
	void RemoveObject (RenderObject &);
};

}}