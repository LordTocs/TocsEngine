#pragma once
#include <Tocs/Graphics/Texture.h>
#include <Tocs/Graphics/Buffer.h>
#include <Tocs/Graphics/BufferTexture.h>
#include <Tocs/Math/Vector.h>
#include <Tocs/Graphics/Query.h>
#include <Tocs/Graphics/ShaderState.h>

#include "FullscreenQuad.h"


namespace Tocs {
namespace Rendering {

	class RenderSystem;

class ABuffer
{
	Graphics::Texture2D Semaphore;
	Graphics::Texture2D PageIndices;
	Graphics::Texture2D FragCount;

	unsigned int PageCount;
	unsigned int PageSize;

	Graphics::Buffer<Math::Color> ColorPageBuffer;
	Graphics::Buffer<float> DepthPageBuffer;
	Graphics::Buffer<unsigned char> ModePageBuffer;
	Graphics::Buffer<unsigned int> PageLinkBuffer;
	

	Graphics::Buffer<unsigned int> AtomicPageCounter;
	Graphics::Query SampleQuery;

	Graphics::BufferTexture PageLinks;
	Graphics::BufferTexture ColorPages;
	Graphics::BufferTexture DepthPages;
	Graphics::BufferTexture ModePages;

	FullscreenQuad Quad;
	Graphics::ShaderState Inputs;
public:
	

	ABuffer(RenderSystem &system);

	void Bind();
	void UnBind();

	void BlendAndPresent(RenderSystem &system);
	void Clear(RenderSystem &system);

	void CheckPageSizes(RenderSystem &system);

	const Graphics::ShaderState &GetInputs() const { return Inputs; }
	
};

}}