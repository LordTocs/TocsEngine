#pragma once
#include <Tocs/Graphics/CubeMapArray.h>
#include <Tocs/Graphics/RenderTarget.h>
#include <Tocs/Graphics/ShaderState.h>
#include "Camera.h"
#include "Light.h"
namespace Tocs {
namespace Rendering {

class RenderSystem;

class ShadowManager
{
	unsigned int PointLights;
	unsigned int ShadowMapSize;
	Graphics::CubeMapArray PointLightShadows;
	Graphics::RenderTarget ShadowTarget;
	Camera ShadowCamera;
	Graphics::ShaderState ShaderInputs;

public:
	ShadowManager(RenderSystem &system);
	ShadowManager(ShadowManager &&moveme);
	ShadowManager &operator= (ShadowManager &&moveme);

	ShadowManager(const ShadowManager &) = delete;
	ShadowManager &operator= (const ShadowManager &) = delete;

	void AssignShadowMaps(RenderSystem &system);

	void GenerateShadowMap(RenderSystem &system, Light &light);

	Graphics::CubeMapArray &GetShadowMaps() { return PointLightShadows; }
	const Graphics::CubeMapArray &GetShadowMaps() const { return PointLightShadows; }

	void DebugSave(const std::string &fileprefix) const;

	Graphics::ShaderState &GetShaderInputs() { return ShaderInputs; }
};

}}

