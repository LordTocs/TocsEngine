#include "PermutationValueSet.h"
#include <iostream>
#include <Tocs/Core/Tokenizer.h>
#include <Tocs/Core/Float.h>
#include <Tocs/Graphics/Texture.h>
#include <Tocs/Math/Color.h>

using namespace std;
using namespace Tocs::Lexing;
using namespace Tocs::Graphics;
using namespace Tocs::Math;
namespace Tocs {
namespace Rendering {
namespace Permutations {


PermutationValueSet::PermutationValueSet(const PermutationValueSet &copyme)
{
	for (auto i = copyme.Values.begin (); i != copyme.Values.end (); ++i)
	{
		Values[i->first] = std::unique_ptr<PermutationValue> (i->second.get()->Clone ());
	}
}

PermutationValueSet::PermutationValueSet (const std::string &config)
{
	StringSource source(config);
	Tokenizer tokens(source);

	while (!tokens.EndOfStream ())
	{
		while (!tokens.EndOfStream () && tokens.PeekType () == TokenType::Comment) {tokens.GetToken ();}
		string prop = tokens.GetToken ();
		if (!tokens.Is(":"))
		{
			cout << "Permtaton Value Set Parse Error." << endl;
		}
		auto valuetoken = tokens.GetTokenData ();
		if (valuetoken == "map")
		{
			//Its a texture
			if (!tokens.Is ("("))
			{ }

			auto filedata = tokens.GetTokenData ();
			if (filedata.GetType () != TokenType::StringLiteral)
			{ }

			if (!tokens.Is (")"))
			{ }

			
			if (tokens.Is("."))
			{
				auto componenttoken = tokens.GetToken ();
				char component = componenttoken[0];
				Set (prop, new TextureComponentValue (Asset<Texture2D>::Load(filedata.GetToken ()),component));
			}
			else
			{
				const std::string &filename = filedata.GetToken().substr(1,filedata.GetToken().length ()-2);
				Set (prop, new TextureValue (Asset<Texture2D>::Load(filename)));
			}

		
		}
		else if (valuetoken == "#")
		{
			//Its a hexcolor
			auto colortoken = tokens.GetToken ();
			Set(prop, new ConstantValue<Color> (Color::FromHex (string("#") + colortoken)));

		}
		else if (valuetoken == "<")
		{
			//Its a vector
			float v0 = Float::Parse (tokens.GetToken ());
			if (!tokens.Is (","))
			{ }
			float v1 = Float::Parse (tokens.GetToken ());
			if (!tokens.Is (","))
			{ }
			float v2 = Float::Parse (tokens.GetToken ());
			Set (prop, new ConstantValue<Vector3> (Vector3(v0,v1,v2)));

		}
		else if (valuetoken.GetType() == TokenType::Integer || valuetoken.GetType () == TokenType::Float)
		{
			float v = Float::Parse (valuetoken.GetToken ());
			Set (prop, new ConstantValue<float> (v));
		}
		
	}
}

}}}