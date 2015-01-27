#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/GraphicsContext.h>
#include <Tocs/Graphics/Texture.h>
#include <Tocs/Graphics/DepthStencilBuffer.h>
#include <Tocs/Graphics/RenderTarget.h>
#include <Tocs/Graphics/ShaderState.h>
#include <Tocs/Graphics/Shader.h>
#include "Camera.h"
#include "FullscreenQuad.h"
namespace Tocs {
namespace Rendering {

class RenderSystem;

class GBuffer
{
	Graphics::Texture2D Albedo;
	Graphics::Texture2D Specular;
	Graphics::Texture2D Normals;
	Graphics::RenderTarget Target;
	Asset<Graphics::Shader> LightingShader;
	FullscreenQuad Quad;
	Graphics::ShaderStateSet ShadingSet;
	Graphics::ShaderState DeferredBuffers;
public:
	GBuffer(RenderSystem &system);

	void Bind ();
	void UnBind ();
	void Clear ();

	Graphics::Texture2D &GetAlbedo () { return Albedo; }
	Graphics::Texture2D &GetSpecular () { return Specular; }
	Graphics::Texture2D &GetNormals () { return Normals; }
	const Graphics::Texture2D &GetAlbedo () const { return Albedo; }
	const Graphics::Texture2D &GetSpecular () const { return Specular; }
	const Graphics::Texture2D &GetNormals () const { return Normals; }

	void DoLighting(Graphics::GraphicsContext &constext, RenderSystem &system, const Camera &camera);
};

}}