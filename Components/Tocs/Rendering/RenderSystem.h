#pragma once
#include <vector>
#include "Camera.h"
#include <Tocs/Core/Asset.h>
#include "Pipeline.h"
#include "FullscreenQuad.h"
#include "Light.h"
#include <Tocs/Graphics/GraphicsContext.h>
#include <Tocs/Graphics/RenderTarget.h>
#include <Tocs/Graphics/Shader.h>
#include "LightGrid.h"
#include "ABuffer.h"
#include "GBuffer.h"
#include "ShadowManager.h"
namespace Tocs {
namespace Rendering {

class Drawable;

//Holds all objects in the scene, handles rendering and updating
class RenderSystem
{

	RenderSystem (const RenderSystem &); //no copying...
	RenderSystem &operator= (const RenderSystem &);

	Graphics::GraphicsContext *GContext;
	//Replace with better scene container.
	//std::vector<RenderObject *> Objects;
	std::vector<Light *> Lights;
	std::vector<Drawable *> Drawables;
public:
	Graphics::Texture2D FrameResult;
	Graphics::DepthStencilBuffer FrameDepth;
	Graphics::RenderTarget FrameTarget;
private:
	LightGrid LightTiles;
	ABuffer AlphaBuffer;
	GBuffer GeometryBuffer;
	ShadowManager Shadows;

	FullscreenQuad RenderingQuad;
	Asset<Graphics::Shader> QuadShader;

	void PushResult (Graphics::GraphicsContext &context);
	
public:
	Pipeline Pipes;

	Graphics::GraphicsContext &Context() { return *GContext; }
	const Graphics::GraphicsContext &Context() const { return *GContext; }

	friend class RenderObject;
	RenderSystem(Graphics::GraphicsContext &context);
	void Update (float dt);
	void Render (const Camera &camera);

	void Add(Light &light);
	void Add(Drawable &drawable);

	const std::vector<Light *> &GetLights() const { return Lights;  }

	LightGrid &GetLightTiles() { return LightTiles; }
	const LightGrid &GetLightTiles() const { return LightTiles; }

	ABuffer &GetAlphaBuffer() { return AlphaBuffer; }
	const ABuffer &GetAlphaBuffer() const { return AlphaBuffer; }

	GBuffer &GetGeometryBuffer() { return GeometryBuffer; }
	const GBuffer &GetGeometryBuffer() const { return GeometryBuffer; }

	ShadowManager &GetShadows() { return Shadows; }
	const ShadowManager &GetShadows() const { return Shadows; }
};

}}