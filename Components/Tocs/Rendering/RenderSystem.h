#pragma once
#include <vector>
#include "Camera.h"
#include <Tocs/Core/Asset.h>
#include "Pipeline.h"
#include "FullscreenQuad.h"
#include <Tocs/Graphics/GraphicsContext.h>
#include <Tocs/Graphics/RenderTarget.h>
#include <Tocs/Graphics/Shader.h>
namespace Tocs {
namespace Rendering {


//Holds all objects in the scene, handles rendering and updating
class RenderSystem
{
	RenderSystem (const RenderSystem &); //no copying...
	RenderSystem &operator= (const RenderSystem &);
	//Replace with better scene container.
	//std::vector<RenderObject *> Objects;
	//FullscreenQuad RenderingQuad;
	Asset<Graphics::Shader> QuadShader;

	void PushResult (Graphics::GraphicsContext &context);
public:
	Graphics::Texture2D FrameResult;
	Graphics::DepthStencilBuffer FrameDepth;
	Graphics::RenderTarget FrameTarget;
	Pipeline Pipes;

	friend class RenderObject;
	RenderSystem(Graphics::GraphicsContext &context);
	void Update (float dt);
	void Render (Graphics::GraphicsContext &context, const Camera &camera);
};

}}