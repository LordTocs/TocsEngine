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
	Math::Color WireColor;
public:
	WireframeShader();
	WireframeShader(const WireframeShader &) = delete;
	WireframeShader(WireframeShader &&moveme)
		: WireColor(moveme.WireColor) {}

	static WireframeShader ParseFromConfig(const std::string &config);

	Pipe &GetPipe(RenderSystem &system) const;
	void LinkShaderCode(ShaderConstruction &construction) const;
	void QueueJob(JobProxy &proxy, RenderSystem &system, Graphics::ShaderState &inputs) const;
};

}}

