#pragma once
#include "ParticleController.h"
#include <Tocs/Core/Tokenizer.h>
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/Shader.h>
namespace Tocs {
namespace Rendering {

class ShaderController : public ParticleController
{
	float t;
	NullableAsset<Graphics::Shader> UpdateShader;
public:
	ShaderController();
	ShaderController(ShaderController &&moveme);

	void Update(float dt, ParticleDataBuffer &data, RenderSystem &system);

	ParticleController *Clone() const;

	static ShaderController Parse(const ParticleDescription& desc, Lexing::Tokenizer &tokens);
};

}}