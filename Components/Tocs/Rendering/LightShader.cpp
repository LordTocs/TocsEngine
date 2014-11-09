#include "LightShader.h"
#include <Tocs/Core/Float.h>
#include <Tocs/Core/Integer.h>
#include <Tocs/Core/Tokenizer.h>
#include <fstream>
#include "RenderSystem.h"
using namespace Tocs::Lexing;

namespace Tocs {
namespace Rendering {

void LightShader::LinkShaderCode (ShaderConstruction &construction) const
{
	static Asset<Graphics::ShaderCode> evaluator = Asset<Graphics::ShaderCode>::Load("shaders/TileShadingEvaluator.frag");

	construction.AddCode(Template.Get().GetShaderCode(Inputs));
	construction.AddCode(evaluator.Get());
	construction.AddCode(Transparency.GetCompositor());

}

Pipe &LightShader::GetPipe(RenderSystem &system) const
{
	if (Transparency == TransparencyType::Opaque)
		return system.Pipes.OpaquePipe;
	else
		return system.Pipes.TransparentPipe;
}

void LightShader::QueueJob(JobProxy &proxy, RenderSystem &system, Graphics::ShaderState &inputs) const
{
	Inputs.Apply(inputs,Template.Get());
	proxy.Get().StateSet.MapState(system.GetLightTiles().GetShaderInputs());
	proxy.Get().StateSet.MapState(system.GetShadows().GetShaderInputs());
}

LightShader LightShader::ParseFromConfig(const std::string &config)
{
	Lexing::StringSource source(config);

	Lexing::Tokenizer tokens(source);

	LightShader result;

	while (!tokens.EndOfStream())
	{
		if (tokens.Is("source"))
		{
			if (!tokens.Is(":"))
			{
				std::cout << "ERROR!" << std::endl;
			}

			auto t = tokens.GetTokenData();
			if (t != Lexing::TokenType::StringLiteral)
			{
				std::cout << "ERROR!" << std::endl;
			}

			result.Template = Asset<ShaderPermutationTemplate>::Load(t.GetToken().substr(1, t.GetToken().length() - 2));
		}
		else if (tokens.Is("transparency"))
		{
			if (!tokens.Is("additive"))
			{
				result.Transparency = TransparencyType::AlphaBlending;
			}
			else
			{
				result.Transparency = TransparencyType::AdditiveBlending;
			}
		}
		else if (tokens.Is("i"))
		{
			if (!tokens.Is(":"))
			{
				std::cout << "ERROR!" << std::endl;
			}

			std::string uniform = tokens.GetToken();

			result.Inputs[uniform].ParseValue(tokens);
		}
		else
		{
			//Strange token pop it
			tokens.GetToken();
		}
	}

	return result; 
}

}}
