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
	static Asset<Graphics::ShaderCode> transparentcompositor = Asset<Graphics::ShaderCode>::Load("transparency/Compositor.frag");
	static Asset<Graphics::ShaderCode> opaquecompositor = Asset<Graphics::ShaderCode>::Load("FrameBufferCompositor.frag");
	static Asset<Graphics::ShaderCode> evaluator = Asset<Graphics::ShaderCode>::Load("TileShadingEvaluator.frag");

	construction.AddCode(Template.Get().GetShaderCode(Inputs));
	construction.AddCode(evaluator.Get());
	if (Transparency)
	{
		construction.AddCode(transparentcompositor.Get());
	}
	else
	{
		construction.AddCode(opaquecompositor.Get());
	}

}

JobProxy LightShader::QueueJob(Geometry &geometry, RenderSystem &system) const
{
	ShaderConstruction construction;
	LinkShaderCode(construction);
	geometry.LinkShaders(construction, false);

	JobProxy proxy;
	if (!Transparency)
		proxy = system.Pipes.OpaquePipe.Add(geometry.GetCall(), construction.Link(ShaderPool::Global));
	else
		proxy = system.Pipes.TransparentPipe.Add(geometry.GetCall(), construction.Link(ShaderPool::Global));
	Inputs.Apply(proxy.Get().Input,Template.Get());
	proxy.Get().Input.ApplyMap(system.GetLightTiles().GetShaderInputs());
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

	return result; 
}

}}
