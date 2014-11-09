#include "WireframeShader.h"
#include <Tocs/Core/Float.h>
#include <Tocs/Core/Integer.h>
#include <Tocs/Core/Tokenizer.h>
#include "RenderSystem.h"
namespace Tocs {
namespace Rendering {

Asset<Graphics::ShaderCode> WireframeShader::LoadWireShader()
{
	return Asset<Graphics::ShaderCode>::Load("shaders/SolidColor.frag");
}
FirstUseStatic<Asset<Graphics::ShaderCode>, WireframeShader::LoadWireShader> WireframeShader::WireShader;

WireframeShader::WireframeShader()
{

}

WireframeShader WireframeShader::ParseFromConfig(const std::string &config)
{
	Lexing::StringSource source(config);

	Lexing::Tokenizer tokens(source);

	WireframeShader result;

	while (!tokens.EndOfStream())
	{
		if (tokens.Is("color"))
		{
			if (!tokens.Is(":"))
			{//OHGODWHAT
			}

			if (!tokens.Is("#"))
			{
			}

			auto colortoken = tokens.GetToken();
			result.WireColor = Math::Color::FromHex(std::string("#") + colortoken);
		}
	}

	return result;
}

void WireframeShader::LinkShaderCode(ShaderConstruction &construction) const
{
	construction.AddCode(WireShader.Get().Get());
}

Pipe &WireframeShader::GetPipe(RenderSystem &system) const
{
	return system.Pipes.WireframePipe;
}

void WireframeShader::QueueJob(JobProxy &proxy, RenderSystem &system, Graphics::ShaderState &inputs) const
{
	inputs.AddValue("Color");
	inputs["Color"].Ref(WireColor);
}

}}