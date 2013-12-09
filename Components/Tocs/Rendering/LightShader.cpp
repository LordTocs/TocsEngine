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
	for (auto i = Sources.begin (); i != Sources.end (); ++i)
	{
		construction.AddCode ((*i).Get());
	}
	Evaluator.LinkShaderCode(construction);
	CompositingShader.get()->LinkShaderCode(construction);  
}

JobProxy LightShader::QueueJob(Geometry &geometry, Pipeline &pipeline) const
{
	ShaderConstruction construction;
	LinkShaderCode(construction);
	geometry.LinkShaders(construction, false);

	JobProxy proxy = pipeline.ForwardPipe.Add(geometry.GetCall(), construction.Link(ShaderPool::Global));
	proxy.Get().Input.ApplyMap(this->Inputs);

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

			result.Sources.emplace_back(Asset<Graphics::ShaderCode>::Load(t.GetToken().substr(1, t.GetToken().length() - 2)));
		}
		else if (tokens.Is("transparency"))
		{
			result.Transparency = true;
		}
		else if (tokens.Is("u"))
		{
			if (!tokens.Is(":"))
			{
				std::cout << "ERROR!" << std::endl;
			}

			std::string uniform = tokens.GetToken();

			auto valuedata = tokens.GetTokenData();

			if (valuedata == TokenType::Float)
			{
				result.Inputs[uniform].Value(Float::Parse(valuedata.GetToken()));
			}
			else if (valuedata == TokenType::Integer)
			{
				result.Inputs[uniform].Value(Integer::Parse32(valuedata.GetToken()));
			}
			else if (valuedata == "tex")
			{
				if (!tokens.Is("("))
				{
				}

				TokenData filetoken = tokens.GetTokenData();
				if (filetoken.GetType() != TokenType::StringLiteral)
				{
				}

				std::string filename = filetoken.GetToken().substr(1, filetoken.GetToken().size() - 2);

				if (!tokens.Is(")"))
				{
				}

				result.Textures.emplace_back(Asset<Graphics::Texture2D>::Load(filename));

				result.Inputs[uniform].Ref(result.Textures[result.Textures.size() - 1].Get());
			}
			else if (valuedata == "<")
			{
				float v0 = Float::Parse(tokens.GetToken());
				if (!tokens.Is(","))
				{
				}
				float v1 = Float::Parse(tokens.GetToken());
				if (!tokens.Is(","))
				{
				}
				float v2 = Float::Parse(tokens.GetToken());
				if (!tokens.Is(">"))
				{
				}

				result.Inputs[uniform].Value(Math::Vector3(v0, v1, v2));
			}
			else if (valuedata == "#")
			{
				auto colortoken = tokens.GetToken();
				result.Inputs[uniform].Value(Math::Color::FromHex(std::string("#") + colortoken));
			}

		}
	}

	result.CompositingShader = std::unique_ptr<Compositor>(new FrameBufferCompositor());

	return result; 
}

}}
