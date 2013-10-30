#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/Shader.h>
#include <Tocs/Graphics/Texture.h>
#include <Tocs/Graphics/Buffer.h>
#include <Tocs/Graphics/BufferTexture.h>
#include <Tocs/Math/Vector4i.h>
#include <Tocs/Math/Vector4.h>

#include "LightShader.h"
#include "Geometry.h"
#include "Pipeline.h"
#include "RenderSystem.h"
#include "Job.h"
#include "ShaderPool.h"
#include "Light.h"
#include <vector>

#include <Tocs/Math/Vector2.h>

namespace Tocs {
namespace Rendering {

class LightEvaluator
{
	//Must supply vec4 Evaluate ();
	Asset<Graphics::ShaderCode> EvaluationShader;

	Graphics::Buffer<Math::Vector4i> LightGrid;

	Graphics::Buffer<int> LightIndexLists;
	Graphics::BufferTexture LightIndexListsTexture;

	Graphics::Buffer<Math::Vector4> PositionRange;
	Graphics::Buffer<Math::Vector4> ColorBuffer;


	const static int MaxTilesWide;
	const static int MaxTilesHigh;

	int TilesWide;
	int TilesHigh;

	class ScreenRectangle
	{
	public:
		Math::Vector2 Min;
		Math::Vector2 Max;

	};

public:
	LightEvaluator (RenderSystem &system, Graphics::GraphicsContext &context);
	Graphics::UniformMap Inputs;
	Job CreatePrepassJob (Geometry &geometry, Pipeline &pipeline);
	void LinkShaderCode (ShaderConstruction &construction);

	void Configure (const Camera &camera, const std::vector<Light *> &lights);


};

}}