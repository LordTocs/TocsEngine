#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/ShaderCode.h>
#include <Tocs/Graphics/UniformMap.h>
#include "ShaderPermutationTemplate.h"
#include "ShaderPermutationInput.h"
#include "ShaderPool.h"
#include <vector>
#include "Material.h"
#include "LightEvaluator.h"
#include "Compositor.h"
namespace Tocs {
namespace Rendering {



class LightShader : public MaterialComponentSource
{
	//Must supply Shade (vec4 LightDir, vec4 ViewDir, vec4 LightColor, float Attenuation)
	NullableAsset<ShaderPermutationTemplate> Template;
	ShaderPermutationInput Inputs;
	bool Transparency;

	LightEvaluator Evaluator;
	std::unique_ptr<Compositor> CompositingShader;
public:
	LightShader () : Transparency (false) {}

	LightShader(LightShader &&moveme)
		: Inputs(std::move(moveme.Inputs)),
		Transparency(moveme.Transparency),
		Evaluator(std::move(moveme.Evaluator)),
		CompositingShader(std::move(moveme.CompositingShader)),
		Template(std::move(moveme.Template))
	{} 

	LightShader(const LightShader &) = delete;

	static LightShader ParseFromConfig(const std::string &config);

	bool HasTransparency () const { return Transparency; }

	void LinkShaderCode(ShaderConstruction &construction) const;
	JobProxy QueueJob(Geometry &geometry, Pipeline &pipeline) const;
};

}}
