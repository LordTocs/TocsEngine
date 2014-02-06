#pragma once
#include <Tocs/Graphics/Texture.h>
#include <Tocs/Graphics/RenderTarget.h>
#include "PostProcess.h"

namespace Tocs {
namespace Rendering {

class BloomAndGlow : public PostProcess
{
	Graphics::Texture2D GlowBuffer;
	Graphics::DepthStencilBuffer GlowDepthBuffer;
	Graphics::RenderTarget GlowTarget;
public:
	BloomAndGlow(RenderSystem &system);

	void Apply(const Graphics::Texture2D &sourcetexture, Graphics::RenderTarget &target);


};


}}