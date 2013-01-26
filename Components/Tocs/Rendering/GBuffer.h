#pragma once
#include <Tocs/Graphics/GraphicsContext.h>
#include <Tocs/Graphics/Texture.h>
#include <Tocs/Graphics/DepthStencilBuffer.h>
#include <Tocs/Graphics/RenderTarget.h>
namespace Tocs {
namespace Rendering {

class GBuffer
{
	Graphics::Texture2D Albedo;
	Graphics::Texture2D Specular;
	Graphics::Texture2D Normals;
	Graphics::Texture2D LinearDepth;
	Graphics::DepthStencilBuffer Depth;
	Graphics::RenderTarget Target;
public:
	GBuffer(Graphics::GraphicsContext &context);

	void Bind ();
	void UnBind ();
};

}}