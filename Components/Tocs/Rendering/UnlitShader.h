#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/ShaderCode.h>
#include "ShaderPermutationTemplate.h"
#include "ShaderPermutationInput.h"
#include "ShaderPool.h"
#include "TransparencyType.h"
#include <vector>
#include "Material.h"

namespace Tocs {
namespace Rendering {

class UnlitShader : public MaterialComponentSource
{
	NullableAsset<ShaderPermutationTemplate> Template;
	ShaderPermutationInput Inputs;
	TransparencyType Transparency;
public:
	UnlitShader() {}
	UnlitShader(UnlitShader &&moveme)
		: Inputs(std::move(moveme.Inputs)),
		Transparency(moveme.Transparency),
		Template(std::move(moveme.Template))
	{}

	UnlitShader(const UnlitShader &) = delete;

	static UnlitShader ParseFromConfig(const std::string &config);

	Pipe &GetPipe(RenderSystem &system) const;
	void LinkShaderCode(ShaderConstruction &construction) const;
	void QueueJob(JobProxy &proxy, RenderSystem &system, Graphics::ShaderState &inputs) const;
};

}}