#pragma once
#include <Tocs/Graphics/Texture.h>
#include "SMAA.h"
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

	SMAA AntiAliasing;
public:
	PostProcessing(RenderSystem &system);

	void Apply();

	Graphics::Texture2D &GetCurrentFrameResult();
	Graphics::RenderTarget &GetCurrentFrameTarget();

	void FlipTarget();
};

}}