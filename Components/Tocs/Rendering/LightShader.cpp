#include "LightShader.h"
#include <Tocs/Core/Float.h>
#include <Tocs/Core/Integer.h>
#include <Tocs/Core/Tokenizer.h>
#include <fstream>

using namespace Tocs::Lexing;

namespace Tocs {
namespace Rendering {

void LightShader::LinkShaderCode (ShaderConstruction &construction) const
{
	construction.AddCode(Template.Get().GetShaderCode(Inputs));
	Evaluator.LinkShaderCode(construction);
	CompositingShader.get()->LinkShaderCode(construction);  
}

JobProxy LightShader::QueueJob(Geometry &geometry, Pipeline &pipeline) const
{
	ShaderConstruction construction;
	LinkShaderCode(construction);
	geometry.LinkShaders(construction, false);

	JobProxy proxy = pipeline.ForwardPipe.Add(geometry.GetCall(), construction.Link(ShaderPool::Global));
	Inputs.Apply(proxy.Get().Input,Template.Get());

	return proxy;
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
			result.Transparency = true;
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

	result.CompositingShader = std::unique_ptr<Compositor>(new FrameBufferCompositor());

	return result; 
}

}}
