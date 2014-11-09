#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/ShaderCode.h>
#include "ShaderPermutationTemplate.h"
#include "ShaderPermutationInput.h"
#include "ShaderPool.h"
#include <vector>
#include "Material.h"
#include "TransparencyType.h"

namespace Tocs {
namespace Rendering {



class LightShader : public MaterialComponentSource
{
	//Must supply Shade (vec4 LightDir, vec4 ViewDir, vec4 LightColor, float Attenuation)
	NullableAsset<ShaderPermutationTemplate> Template;
	ShaderPermutationInput Inputs;
	TransparencyType Transparency;
public:
	LightShader () {}

	LightShader(LightShader &&moveme)
		: Inputs(std::move(moveme.Inputs)),
		Transparency(moveme.Transparency),
		Template(std::move(moveme.Template))
	{} 

	LightShader(const LightShader &) = delete;

	LightShader &operator= (const LightShader &) = delete;

	static LightShader ParseFromConfig(const std::string &config);

	Pipe &GetPipe(RenderSystem &system) const;
	void LinkShaderCode(ShaderConstruction &construction) const;
	void QueueJob(JobProxy &proxy, RenderSystem &system, Graphics::ShaderState &inputs) const;
};

}}
