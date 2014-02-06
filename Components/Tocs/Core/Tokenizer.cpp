#include "Tokenizer.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <streambuf>
#include "Character.h"
using namespace std;



namespace Tocs {
namespace Lexing{

const TokenType TokenType::Word (word);
const TokenType TokenType::Integer (integer);
const TokenType TokenType::Float (_float);
const TokenType TokenType::StringLiteral (stringliteral);
const TokenType TokenType::Comment (comment);
const TokenType TokenType::MultiLineComment (multilinecomment);
const TokenType TokenType::Symbol (symbol);


StringSource StringSource::FromFile(const std::string &file)
{
	std::ifstream t(file);

	if (!t.good())
		return StringSource ("");

	std::string str;

	t.seekg(0, std::ios::end);   
	str.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),
				std::istreambuf_iterator<char>());

	return StringSource (str);
}

void Tokenizer::LexNext ()
{
	stringstream white;
	stringstream result;
	TokenType type (TokenType::Word);
	bool escaped = false;
	char enclosingchar = ' ';
	bool isslash = false;
	Token = "";

	if (Source.EndOfSource ())
	{ End = true; return; }

	//Skip Whitespace
	while (!Source.EndOfSource () && Character::IsWhiteSpace (Source.PeekChar ()))
	{ white << Source.GetChar (); }

	if (Source.EndOfSource ())
	{ End = true; return; }

	char c = Source.PeekChar ();
	if (c == '_' || Character::IsLetter(c))
	{
		type = TokenType::Word;
	}
	else if (Character::IsNumber (c))
	{
		type = TokenType::Integer;
	}
	else if (c == '"'  || c== '\'')
	{
		type = TokenType::StringLiteral;
		enclosingchar = c;
	}
	else
	{
		type = TokenType::Symbol;
		if (c == '/')
		{
			isslash = true;
		}
	}
	Type = type;
	result << Source.GetChar ();
	
	while (true)
	{
		if (Source.EndOfSource ())
		{ End = true; Token = result.str(); return; }

		c = Source.PeekChar ();

		if (type == TokenType::Word)
		{
			if (c == '_' || Character::IsLetter(c) || Character::IsNumber(c))
			{
				result << Source.GetChar();
			}
			else
			{
				Token = result.str();
				WhiteSpace = white.str ();
				Type = type;
				return;
			}
		}
		else if (type == TokenType::Integer)
		{
			if (Character::IsNumber(c))
			{
				result << Source.GetChar ();
			}
			else if (c == '.')
			{
				result << Source.GetChar();
				type = TokenType::Float;
			}
			else
			{
				Token = result.str ();
				WhiteSpace = white.str ();
				Type = type;
				return;
			}
		}
		else if (type== TokenType::Float)
		{
			if (Character::IsNumber(c))
			{
				result << Source.GetChar ();
			}
			else
			{
				Token = result.str ();
				WhiteSpace = white.str ();
				Type = type;
				return;
			}
		}
		else if (type == TokenType::Symbol)
		{
			if (isslash && c == '/')
			{
				type = TokenType::Comment;
				result << Source.GetChar ();
			}
			if (result.str()[0] == '-' && result.str().length() == 1 && Character::IsNumber(c))
			{
				type = TokenType::Integer;
				result << Source.GetChar();
			}
			else
			{
				Token = result.str ();
				WhiteSpace = white.str ();
				Type = type;
				return;
			}
		}
		else if (type == TokenType::Comment)
		{
			if (c == '\n')
			{
				Token = result.str ();
				WhiteSpace = white.str ();
				Type = type;
				return;
			}
			else
			{
				result << Source.GetChar ();;
			}
		}
		else if (type == TokenType::StringLiteral)
		{
			if (escaped)
			{
				result << Source.GetChar ();
			}
			else
			{
				if (c == '\\')
				{
					escaped = true;
				}
				else if (c == enclosingchar)
				{
					result << Source.GetChar ();
					Token = result.str ();
					WhiteSpace = white.str ();
					Type = type;
					return;
				}
				else
				{
					result << Source.GetChar ();
				}
			}
		}

	}
}

//Always pop the first opening token
bool Tokenizer::FindClose (const std::string &open, const std::string &close)
{
	int opencount = 1;
	while (!EndOfStream ())
	{
		if (Is(open))
		{
			++opencount;
		}
		else if (Is(close))
		{
			--opencount;
			if(opencount == 0)
				return true;
		}
		else
		{
			LexNext();
		}
	}
	return false;
}

std::string Tokenizer::GetTextIn (const std::string &open, const std::string &close)
{
	int opencount = 0;
	stringstream text;
	if (EndOfStream ())
		return "";
	if (Is(open))
	{
		++opencount;
	}
	else
		return "";
	
	while (!EndOfStream ())
	{
		text << WhiteSpace;
		
		if (Token == open)
		{
			++opencount;
		}
		else if (Token == close)
		{
			--opencount;
			if (opencount == 0)
			{
				LexNext();
				return text.str ();
			}
		}
		text << Token;
		LexNext();
	}

	return text.str ();
}

}}