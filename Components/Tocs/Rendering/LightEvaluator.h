 #pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/Shader.h>
#include <Tocs/Graphics/Texture.h>
#include <Tocs/Graphics/Buffer.h>
#include <Tocs/Graphics/BufferTexture.h>
#include <Tocs/Math/Vector.h>

#include "LightShader.h"
#include "Geometry.h"
#include "Pipeline.h"
#include "RenderSystem.h"
#include "Job.h"
#include "ShaderPool.h"
#include "Light.h"
#include <vector>


namespace Tocs {
namespace Rendering {

class LightEvaluator
{
	//Must supply vec4 Evaluate ();
	Asset<Graphics::ShaderCode> EvaluationShader;

public:
	LightEvaluator (RenderSystem &system, Graphics::GraphicsContext &context);
	Graphics::UniformMap Inputs;
	Job CreatePrepassJob (Geometry &geometry, Pipeline &pipeline);
	void LinkShaderCode (ShaderConstruction &construction);

	void Configure (const Camera &camera, const std::vector<Light *> &lights);


};

}}