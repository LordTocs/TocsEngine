#include "Material.h"
#include <Tocs/Core/Float.h>
#include <Tocs/Core/Integer.h>
#include <Tocs/Math/Color.h>

using namespace Tocs::Lexing;
namespace Tocs {
namespace Rendering {

Material::MaterialComponent Material::MaterialComponent::FromTypeName(const std::string &name)
{
	if (name == "Deferred")
		return MaterialComponent (Asset<MaterialTemplate>::Load("DeferredTemplate.tgl"),"Deferred");
	if (name == "Wireframe")
		return MaterialComponent (Asset<MaterialTemplate>::Load("UnlitTemplate.tgl"),"Wireframe");
	return MaterialComponent (Asset<MaterialTemplate>::Load("UnlitTemplate.tgl"),"NonLit");
}

Material::MaterialComponent::MaterialComponent (Asset<MaterialTemplate> matemplate, std::string pipename)
	: Template(matemplate),
	  PipeName (pipename),
	  Values(Template)
{
}



Material Material::LoadFromFile (const std::string &filename)
{
	Lexing::StringSource source = Lexing::StringSource::FromFile(filename);
	Lexing::Tokenizer tokens (source);

	Material result;

	while (!tokens.EndOfStream ())
	{
		
		while ((tokens.PeekType () == TokenType::Comment || tokens.PeekType () == TokenType::MultiLineComment) && !tokens.EndOfStream())
		{
			tokens.GetToken();
		}

		if (tokens.EndOfStream())
			break;

		TokenData typetoken = tokens.GetTokenData();
		if (tokens.EndOfStream())
			break;
		if (typetoken.GetType () != TokenType::Word)
			break;
		
		TokenData opencurly = tokens.GetTokenData();
		if (opencurly != "{")
			break;

		MaterialComponent component = MaterialComponent::FromTypeName(typetoken.GetToken());
		
		while (true)
		{

			while ((tokens.PeekType () == TokenType::Comment || tokens.PeekType () == TokenType::MultiLineComment) && !tokens.EndOfStream())
			{tokens.GetToken();}

			TokenData valuename = tokens.GetTokenData();
			if (valuename == "}")
				break; //Not a value

			if (!tokens.Is(":"))
			{}

			TokenData valuedata = tokens.GetTokenData();

			if (valuedata.GetType () == TokenType::Float)
			{
				float value = Float::Parse(valuedata.GetToken());
				component.Values[valuename.GetToken()].Value(value);
			}
			else if (valuedata.GetType() == TokenType::Integer)
			{
				int value = Integer::Parse32(valuedata.GetToken());
				component.Values[valuename.GetToken()].Value(value);
			}
			else if (valuedata == "map")
			{
				if (!tokens.Is("("))
				{}

				TokenData filetoken = tokens.GetTokenData ();
				if (filetoken.GetType () != TokenType::StringLiteral)
				{}

				std::string filename = filetoken.GetToken().substr(1,filetoken.GetToken().size()-2);
				
				if (!tokens.Is(")"))
				{}

				if (tokens.Is("."))
				{
					//THERES A SWIZZLE
					TokenData swizzletoken = tokens.GetTokenData();
					component.Values[valuename.GetToken()].MapSwizzle(Asset<Graphics::Texture2D>::Load(filename),swizzletoken.GetToken());
				}
				else
				{
					//THERES NO SWIZZLE
					component.Values[valuename.GetToken()].Map(Asset<Graphics::Texture2D>::Load(filename));
				}
			}
			else if (valuedata == "function")
			{
				std::string functionbody = tokens.GetTextIn("{","}");
				component.Values[valuename.GetToken()].Function(functionbody);
			}
			else if (valuedata == "#")
			{
				//Its a hexcolor
				auto colortoken = tokens.GetToken ();
				component.Values[valuename.GetToken()].Value(Math::Color::FromHex (std::string("#") + colortoken));
			}
			else if (valuedata == "<")
			{
				//Its a vector
				float v0 = Float::Parse (tokens.GetToken ());
				if (!tokens.Is (","))
				{ }
				float v1 = Float::Parse (tokens.GetToken ());
				if (!tokens.Is (","))
				{ }
				float v2 = Float::Parse (tokens.GetToken ());
				component.Values[valuename.GetToken()].Value(Math::Vector3(v0,v1,v2));
				if (!tokens.Is(">"))
				{ }
			}
		}

		result.Components.push_back(component);
	}

	return std::move(result);
}

Material::Material(Material &&moveme)
	: Components(std::move(moveme.Components))
{
}



}}