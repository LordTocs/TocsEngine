#include "UnlitShader.h"
#include "RenderSystem.h"

namespace Tocs {
namespace Rendering {


void UnlitShader::LinkShaderCode(ShaderConstruction &construction) const
{
	static Asset<Graphics::ShaderCode> transparentcompositor = Asset<Graphics::ShaderCode>::Load("shaders/transparency/Compositor.frag");
	static Asset<Graphics::ShaderCode> opaquecompositor = Asset<Graphics::ShaderCode>::Load("shaders/FrameBufferCompositor.frag");

	construction.AddCode(Template.Get().GetShaderCode(Inputs));
	if (Transparency)
	{
		construction.AddCode(transparentcompositor.Get());
	}
	else
	{
		construction.AddCode(opaquecompositor.Get());
	}

}

JobProxy UnlitShader::QueueJob(Geometry &geometry, RenderSystem &system) const
{
	ShaderConstruction construction;
	LinkShaderCode(construction);
	geometry.LinkShaders(construction, false);

	JobProxy proxy;
	Graphics::Shader *shader = &construction.Link(ShaderPool::Global);

	shader->PrintDebugInformation();

	if (!Transparency)
		proxy = system.Pipes.OpaquePipe.Add(geometry.GetCall(), *shader);
	else
		proxy = system.Pipes.TransparentPipe.Add(geometry.GetCall(), *shader);
	Inputs.Apply(proxy.Get().Input, Template.Get());

	return proxy;
}

UnlitShader UnlitShader::ParseFromConfig(const std::string &config)
{
	Lexing::StringSource source(config);

	Lexing::Tokenizer tokens(source);

	UnlitShader result;

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

	return result;
}

}}
