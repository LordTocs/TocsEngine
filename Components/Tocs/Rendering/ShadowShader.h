#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/ShaderCode.h>
#include "ShaderPermutationTemplate.h"
#include "ShaderPermutationInput.h"
#include "ShaderPool.h"
#include <vector>
#include "Material.h"
namespace Tocs {
namespace Rendering {

class ShadowShader : public MaterialComponentSource
{
	NullableAsset<ShaderPermutationTemplate> Template;
	ShaderPermutationInput Inputs;
public:
	ShadowShader();
	ShadowShader(const ShadowShader &) = delete;
	ShadowShader(ShadowShader &&moveme);


	static ShadowShader ParseFromConfig(const std::string &config);

	Pipe &GetPipe(RenderSystem &system) const;
	void LinkShaderCode(ShaderConstruction &construction) const;
	void QueueJob(JobProxy &proxy, RenderSystem &system, Graphics::ShaderState &inputs) const;
};

}}