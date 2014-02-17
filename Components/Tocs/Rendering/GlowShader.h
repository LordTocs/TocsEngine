#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/ShaderCode.h>
#include <Tocs/Graphics/UniformMap.h>
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

	void LinkShaderCode(ShaderConstruction &construction) const;
	JobProxy QueueJob(Geometry &geometry, RenderSystem &pipeline) const;
};

}}