#include "WireframeShader.h"
#include <Tocs/Core/Float.h>
#include <Tocs/Core/Integer.h>
#include <Tocs/Core/Tokenizer.h>
namespace Tocs {
namespace Rendering {

Asset<Graphics::ShaderCode> WireframeShader::LoadWireShader()
{
	return Asset<Graphics::ShaderCode>::Load("SolidColor.frag");
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
			result.Inputs["Color"].Value(Math::Color::FromHex(std::string("#") + colortoken));
		}
	}

	return result;
}

void WireframeShader::LinkShaderCode(ShaderConstruction &construction) const
{
	construction.AddCode(WireShader.Get().Get());
}

JobProxy WireframeShader::QueueJob(Geometry &geometry, Pipeline &pipeline) const
{
	ShaderConstruction construction;
	LinkShaderCode(construction);
	geometry.LinkShaders(construction, false);
	JobProxy proxy = pipeline.WireframePipe.Add(geometry.GetCall(), construction.Link(ShaderPool::Global));
	proxy.Get().Input.ApplyMap(this->Inputs);
	return proxy;
}

}}