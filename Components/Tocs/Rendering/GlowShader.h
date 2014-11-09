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

class GlowShader : public MaterialComponentSource
{
	NullableAsset<ShaderPermutationTemplate> Template;
	ShaderPermutationInput Inputs;
public:
	GlowShader() {}

	GlowShader(GlowShader &&moveme)
		: Inputs(std::move(moveme.Inputs)),
		  Template(std::move(moveme.Template))
	{}

	GlowShader(const GlowShader &) = delete;

	GlowShader &operator= (const GlowShader &) = delete;

	static GlowShader ParseFromConfig(const std::string &config);

	Pipe &GetPipe(RenderSystem &system) const;
	void LinkShaderCode(ShaderConstruction &construction) const;
	void QueueJob(JobProxy &proxy, RenderSystem &system, Graphics::ShaderState &inputs) const;
};

}}