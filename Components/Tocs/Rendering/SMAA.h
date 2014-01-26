#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/Texture.h>
#include <Tocs/Graphics/RenderTarget.h>
#include <Tocs/Graphics/Shader.h>
#include "FullscreenQuad.h"
namespace Tocs {
namespace Rendering {

class RenderSystem;

class SMAA
{
public:
	Graphics::Texture2D EdgeTex;
	Graphics::RenderTarget EdgeTarget;

	Graphics::Texture2D BlendTex;
	Graphics::RenderTarget BlendTarget;

	Graphics::Texture2D AreaTex;
	Graphics::Texture2D SearchTex;


	Asset<Graphics::Shader> EdgeShader;
	Asset<Graphics::Shader> BlendShader;
	Asset<Graphics::Shader> NeighborhoodShader;

	FullscreenQuad Quad;

	//void BuildShaders();
	void SetupRenderTargets();
	void SetupReferenceTextures();

	RenderSystem *System;

	SMAA(RenderSystem &system);

	void EdgeDetectionPass(const Graphics::Texture2D &albedo);
	void BlendingWeightPass();
	void FinalBlendingPass(const Graphics::Texture2D &albedo);
};

}}