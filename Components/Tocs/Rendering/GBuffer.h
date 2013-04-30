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

	Graphics::Texture2D &GetAlbedo () { return Albedo; }
	Graphics::Texture2D &GetSpecular () { return Specular; }
	Graphics::Texture2D &GetNormals () { return Normals; }
	Graphics::Texture2D &GetLinearDepth () { return LinearDepth; }
	const Graphics::Texture2D &GetAlbedo () const { return Albedo; }
	const Graphics::Texture2D &GetSpecular () const { return Specular; }
	const Graphics::Texture2D &GetNormals () const { return Normals; }
	const Graphics::Texture2D &GetLinearDepth () const { return LinearDepth; }
};

}}