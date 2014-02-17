#pragma once
#include <Tocs/Graphics/Texture.h>
#include "SMAA.h"
#include "BloomAndGlow.h"
namespace Tocs {
namespace Rendering {

class RenderingSystem;

class PostProcessing
{
	RenderSystem *System;

	Graphics::Texture2D FrameResultA;
	Graphics::Texture2D FrameResultB;

	Graphics::RenderTarget FrameTargetA;
	Graphics::RenderTarget FrameTargetB;

	bool Target;

	
public:
	SMAA AntiAliasing;
	BloomAndGlow Glow;

	PostProcessing(RenderSystem &system);

	void Apply();

	Graphics::Texture2D &GetCurrentFrameResult();
	Graphics::RenderTarget &GetCurrentFrameTarget();

	void FlipTarget();
};

}}