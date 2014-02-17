#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/Texture.h>
#include <Tocs/Graphics/RenderTarget.h>
#include <Tocs/Graphics/Shader.h>
#include "PostProcess.h"
#include <Tocs/Graphics/GraphicsContext.h>
#include "FullscreenQuad.h"
namespace Tocs {
namespace Rendering {

class BloomAndGlow : public PostProcess
{
	Graphics::Texture2D GlowBufferA;
	Graphics::Texture2D GlowBufferB;
	Graphics::DepthStencilBuffer GlowDepthBuffer;
	Graphics::RenderTarget GlowTargetA;
	Graphics::RenderTarget GlowTargetB;
	FullscreenQuad Quad;


	Asset<Graphics::Shader> DownsampleDepth;
	Asset<Graphics::Shader> Blur;
	Asset<Graphics::Shader> Composite;
public:
	BloomAndGlow(RenderSystem &system);

	void SetupGlowViewport(Graphics::GraphicsContext &context);

	void ConvertDepthBuffer();

	void Apply(const Graphics::Texture2D &sourcetexture, Graphics::RenderTarget &target);

	Graphics::RenderTarget &GetGlowTarget() { return GlowTargetA; }

	void OutputDebugImages(std::string filebase);

};


}}