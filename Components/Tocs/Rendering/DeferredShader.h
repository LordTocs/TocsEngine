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

class DeferredShader : public MaterialComponentSource
{
	NullableAsset<ShaderPermutationTemplate> Template;
	ShaderPermutationInput Inputs;

public:
	DeferredShader();

	DeferredShader(DeferredShader &&moveme)
		: Inputs(std::move(moveme.Inputs)), Template(std::move(Template)) {}

	DeferredShader(const DeferredShader &) = delete;

	static DeferredShader ParseFromConfig(const std::string &config);

	void LinkShaderCode(ShaderConstruction &construction) const;
	JobProxy QueueJob(Geometry &geometry, RenderSystem &system) const;
};

}}