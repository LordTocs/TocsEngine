#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/ShaderCode.h>
#include <Tocs/Graphics/UniformMap.h>
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
	std::vector<Asset<Graphics::ShaderCode>> Sources;
	std::vector<Asset<Graphics::Texture2D>> Textures;
	bool Transparency;
	Graphics::UniformMap Inputs; 

	LightEvaluator Evaluator;
	std::unique_ptr<Compositor> CompositingShader;
public:
	LightShader () : Transparency (false) {}

	LightShader(LightShader &&moveme)
		: Inputs(std::move(moveme.Inputs)),
		Transparency(moveme.Transparency),
		Sources(std::move(moveme.Sources)),
		Textures(std::move(moveme.Textures)),
		Evaluator(std::move(moveme.Evaluator)),
		CompositingShader(std::move(moveme.CompositingShader))
	{} 

	LightShader(const LightShader &) = delete;

	static LightShader ParseFromConfig(const std::string &config);

	bool HasTransparency () const { return Transparency; }

	void LinkShaderCode(ShaderConstruction &construction) const;
	JobProxy QueueJob(Geometry &geometry, Pipeline &pipeline) const;
};

}}
