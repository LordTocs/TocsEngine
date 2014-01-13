#include "ShadowShader.h"
#include <Tocs/Core/Float.h>
#include <Tocs/Core/Integer.h>
#include <Tocs/Core/Tokenizer.h>
#include <fstream>


namespace Tocs {
namespace Rendering {

ShadowShader::ShadowShader()
{

}


ShadowShader::ShadowShader(ShadowShader &&moveme)
	: Template(std::move(moveme.Template)), Inputs(std::move(moveme.Inputs))
{}


ShadowShader ShadowShader::ParseFromConfig(const std::string &config)
{
	Lexing::StringSource source(config);

	Lexing::Tokenizer tokens(source);

	ShadowShader result;

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

void ShadowShader::LinkShaderCode(ShaderConstruction &construction) const
{
	construction.AddCode(Template.Get().GetShaderCode(Inputs));
}

JobProxy ShadowShader::QueueJob(Geometry &geometry, Pipeline &pipeline) const
{
	ShaderConstruction construction;
	LinkShaderCode(construction);
	geometry.LinkShaders(construction, false);

	JobProxy proxy = pipeline.ShadowPipe.Add(geometry.GetCall(), construction.Link(ShaderPool::Global));

	Inputs.Apply(proxy.Get().Input, Template.Get());

	return proxy;
}


}}