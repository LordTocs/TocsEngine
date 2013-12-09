#pragma once
#include "Material.h"
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/ShaderCode.h>
#include <Tocs/Core/LateStatic.h>

namespace Tocs {
namespace Rendering {

class WireframeShader : public MaterialComponentSource
{
	static Asset<Graphics::ShaderCode> LoadWireShader();
	static FirstUseStatic<Asset<Graphics::ShaderCode>, LoadWireShader> WireShader;
	Graphics::UniformMap Inputs;
public:
	WireframeShader();
	WireframeShader(const WireframeShader &) = delete;
	WireframeShader(WireframeShader &&moveme)
		: Inputs(std::move(moveme.Inputs)) {}

	static WireframeShader ParseFromConfig(const std::string &config);

	void LinkShaderCode(ShaderConstruction &construction) const;
	JobProxy QueueJob(Geometry &geometry, Pipeline &pipeline) const;
};

}}

