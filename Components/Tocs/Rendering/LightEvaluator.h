#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/Shader.h>
#include <Tocs/Graphics/Texture.h>

#include "LightShader.h"
#include "Geometry.h"
#include "Pipeline.h"
#include "RenderSystem.h"
#include "Job.h"
#include "ShaderPool.h"


namespace Tocs {
namespace Rendering {

class LightEvaluator
{
	//Must supply vec4 Evaluate ();
	Asset<Graphics::ShaderCode> EvaluationShader;

	unsigned int TilesWide;
	unsigned int TilesHigh;


public:
	LightEvaluator (RenderSystem &system, Graphics::GraphicsContext &context);
	Graphics::UniformMap Inputs;
	Job CreatePrepassJob (Geometry &geometry, Pipeline &pipeline);
	void LinkShaderCode (ShaderConstruction &construction);

};

}}