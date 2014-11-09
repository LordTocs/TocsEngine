#include "DeferredShader.h"
#include <Tocs/Core/Float.h>
#include <Tocs/Core/Integer.h>
#include <Tocs/Core/Tokenizer.h>
#include <fstream>
#include "RenderSystem.h"

namespace Tocs {
namespace Rendering {

DeferredShader DeferredShader::ParseFromConfig(const std::string &config)
{
	Lexing::StringSource source(config);

	Lexing::Tokenizer tokens(source);

	DeferredShader result;

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
		else if (tokens.Is("i"))
		{
			if (!tokens.Is(":"))
			{
				std::cout << "ERROR!" << std::endl;
			}

			std::string uniform = tokens.GetToken();

			result.Inputs[uniform].ParseValue(tokens);
		}
	}

	return result;
}

void DeferredShader::LinkShaderCode(ShaderConstruction &construction) const
{
	construction.AddCode(Template.Get().GetShaderCode(Inputs));
}

Pipe &DeferredShader::GetPipe(RenderSystem &system) const
{
	return system.Pipes.DeferredPipe;
}

void DeferredShader::QueueJob(JobProxy &proxy, RenderSystem &system, Graphics::ShaderState &inputs) const
{
	Inputs.Apply(inputs, Template.Get());
}


}}