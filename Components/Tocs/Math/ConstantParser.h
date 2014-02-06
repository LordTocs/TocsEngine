#pragma once
#include <Tocs/Core/Tokenizer.h>
#include <Tocs/Core/Float.h>
#include <Tocs/Core/Integer.h>
#include "Vector.h"
namespace Tocs {
namespace Math {

class ConstantParser
{
public:
	ConstantParser() = delete;
	ConstantParser(const ConstantParser &) = delete;

	template <class ValueFunctor>
	static bool TryParse(Lexing::Tokenizer &tokens, ValueFunctor &valuefunc)
	{
		if (tokens.EndOfStream())
			return false;

		std::string type = tokens.PeekToken();


		if (tokens.PeekType() == Lexing::TokenType::Float)
		{
			valuefunc(Float::Parse(tokens.GetToken()));
			return true;
		}
		else if (tokens.PeekType() == Lexing::TokenType::Integer)
		{
			valuefunc(Integer::Parse32(tokens.GetToken()));
			return true;
		}
		if (type == "vec2")
		{
			tokens.GetToken(); //Pop

			Vector2 result;
			if (!tokens.Is("(")){}
			result.X = Float::Parse(tokens.GetToken());
			if (!tokens.Is(",")){}
			result.Y = Float::Parse(tokens.GetToken());
			if (!tokens.Is(")")){}

			valuefunc(result);
			return true;
		}
		else if (type == "vec3")
		{
			tokens.GetToken(); //Pop

			Vector3 result;
			if (!tokens.Is("(")){}
			result.X = Float::Parse(tokens.GetToken());
			if (!tokens.Is(",")){}
			result.Y = Float::Parse(tokens.GetToken());
			if (!tokens.Is(",")){}
			result.Z = Float::Parse(tokens.GetToken());
			if (!tokens.Is(")")){}

			valuefunc(result);
			return true;
		}
		else if (type == "vec4")
		{
			tokens.GetToken(); //Pop

			Vector4 result;
			if (!tokens.Is("(")){}
			result.X = Float::Parse(tokens.GetToken());
			if (!tokens.Is(",")){}
			result.Y = Float::Parse(tokens.GetToken());
			if (!tokens.Is(",")){}
			result.Z = Float::Parse(tokens.GetToken());
			if (!tokens.Is(",")){}
			result.W = Float::Parse(tokens.GetToken());
			if (!tokens.Is(")")){}

			valuefunc(result);
			return true;
		}
		else if (type == "ivec2")
		{
			tokens.GetToken(); //Pop

			Vector2i result;
			if (!tokens.Is("(")){}
			result.X = Integer::Parse32(tokens.GetToken());
			if (!tokens.Is(",")){}
			result.Y = Integer::Parse32(tokens.GetToken());
			if (!tokens.Is(")")){}

			valuefunc(result);
			return true;
		}
		else if (type == "ivec3")
		{
			tokens.GetToken(); //Pop

			Vector3i result;
			if (!tokens.Is("(")){}
			result.X = Integer::Parse32(tokens.GetToken());
			if (!tokens.Is(",")){}
			result.Y = Integer::Parse32(tokens.GetToken());
			if (!tokens.Is(",")){}
			result.Z = Integer::Parse32(tokens.GetToken());
			if (!tokens.Is(")")){}

			valuefunc(result);
			return true;
		}
		else if (type == "ivec4")
		{
			tokens.GetToken(); //Pop

			Vector4i result;
			if (!tokens.Is("(")){}
			result.X = Integer::Parse32(tokens.GetToken());
			if (!tokens.Is(",")){}
			result.Y = Integer::Parse32(tokens.GetToken());
			if (!tokens.Is(",")){}
			result.Z = Integer::Parse32(tokens.GetToken());
			if (!tokens.Is(",")){}
			result.W = Integer::Parse32(tokens.GetToken());
			if (!tokens.Is(")")){}

			valuefunc(result);
			return true;
		}
		else if (type == "uvec2")
		{
			tokens.GetToken(); //Pop

			Vector2ui result;
			if (!tokens.Is("(")){}
			result.X = Integer::ParseU32(tokens.GetToken());
			if (!tokens.Is(",")){}
			result.Y = Integer::ParseU32(tokens.GetToken());
			if (!tokens.Is(")")){}

			valuefunc(result);
			return true;
		}
		else if (type == "uvec3")
		{
			tokens.GetToken(); //Pop

			Vector3ui result;
			if (!tokens.Is("(")){}
			result.X = Integer::ParseU32(tokens.GetToken());
			if (!tokens.Is(",")){}
			result.Y = Integer::ParseU32(tokens.GetToken());
			if (!tokens.Is(",")){}
			result.Z = Integer::ParseU32(tokens.GetToken());
			if (!tokens.Is(")")){}

			valuefunc(result);
			return true;
		}
		else if (type == "uvec4")
		{
			tokens.GetToken(); //Pop

			Vector4ui result;
			if (!tokens.Is("(")){}
			result.X = Integer::ParseU32(tokens.GetToken());
			if (!tokens.Is(",")){}
			result.Y = Integer::ParseU32(tokens.GetToken());
			if (!tokens.Is(",")){}
			result.Z = Integer::ParseU32(tokens.GetToken());
			if (!tokens.Is(",")){}
			result.W = Integer::ParseU32(tokens.GetToken());
			if (!tokens.Is(")")){}

			valuefunc(result);
			return true;
		}

		return false;

	}

};

}}