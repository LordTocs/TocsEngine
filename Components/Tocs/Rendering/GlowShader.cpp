#include "GlowShader.h"
#include <Tocs/Core/Float.h>
#include <Tocs/Core/Integer.h>
#include <Tocs/Core/Tokenizer.h>
#include <fstream>
#include "RenderSystem.h"
using namespace Tocs::Lexing;

namespace Tocs {
namespace Rendering {

GlowShader GlowShader::ParseFromConfig(const std::string &config)
{
	Lexing::StringSource source(config);

	Lexing::Tokenizer tokens(source);

	GlowShader result;

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

void GlowShader::LinkShaderCode(ShaderConstruction &construction) const
{
	construction.AddCode(Template.Get().GetShaderCode(Inputs));
}

JobProxy GlowShader::QueueJob(Geometry &geometry, RenderSystem &system) const
{
	ShaderConstruction construction;
	LinkShaderCode(construction);
	geometry.LinkShaders(construction, false);

	JobProxy proxy = system.Pipes.GlowPipe.Add(geometry.GetCall(), construction.Link(ShaderPool::Global));

	Inputs.Apply(proxy.Get().Input, Template.Get());

	return proxy;
}

}}