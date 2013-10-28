#pragma once
#include <string>
#include "SpecialTokenSet.h"
namespace Tocs {
namespace Lexing {

class TokenType
{
	enum InternalEnum
	{
		word,
		stringliteral,
		integer,
		_float,
		symbol,
		comment,
		multilinecomment
	};
	InternalEnum Internal;

	TokenType (InternalEnum format)
		: Internal (format) {}

public:
	const static TokenType Word;
	const static TokenType Integer;
	const static TokenType Float;
	const static TokenType StringLiteral;
	const static TokenType Symbol;
	const static TokenType Comment;
	const static TokenType MultiLineComment;

	bool operator ==  (const TokenType &op2) const {return Internal == op2.Internal;}
	bool operator !=  (const TokenType &op2) const {return Internal != op2.Internal;}

	std::string ToString () const;
};


class CharSource
{
public:
	virtual char GetChar () = 0;
	virtual char PeekChar () const = 0;
	virtual bool EndOfSource () const = 0;
};

class StringSource : public CharSource
{
	int Index;
	std::string String;
public:
	StringSource (const std::string &str)
		: Index(0), String(str) {}

	char GetChar ()
	{ return String[Index++]; }
	
	char PeekChar () const
	{ return String[Index];	}

	bool EndOfSource () const
	{ return Index >= String.length (); }

	int GetIndex () const 
	{ return Index;	}

	std::string &GetString ()
	{ return String; }

	static StringSource FromFile(const std::string &file);

};

class TokenData
{
	std::string White;
	std::string Tok;
	TokenType Type;
public:
	TokenData(const std::string &w, const std::string &t, const TokenType &type)
		: White(w),
		  Tok(t),
		  Type(type)
	{
	}

	const std::string &GetWhiteSpace() const { return White; }
	const std::string &GetToken () const { return Tok; }
	const TokenType &GetType () const { return Type; }

	bool operator == (const TokenType &type)
	{
		return Type == type;
	}

	bool operator != (const TokenType &type)
	{
		return Type != type;
	}

	bool operator == (const std::string &tok)
	{
		return Tok == tok;
	}

	bool operator != (const std::string &tok)
	{
		return Tok != tok;
	}


};

class Tokenizer
{
	CharSource &Source;
	
	std::string WhiteSpace;
	std::string Token;
	TokenType Type;

	void LexNext ();
	bool End;
public:
	Tokenizer(CharSource &chars)
		: Source(chars),
		  End(false),
		  Type(TokenType::Word)
	{ LexNext(); }
	bool EndOfStream ()
	{ return End; }

	std::string GetToken ()
	{
		std::string temp = Token;
		LexNext ();
		return temp;
	}

	TokenData GetTokenData ()
	{
		TokenData result (WhiteSpace,Token,Type);
		LexNext ();
		return result;
	}

	std::string PeekToken ()
	{
		return Token;
	}

	TokenType PeekType ()
	{
		return Type;
	}

	bool Is(const std::string &expectedtoken)
	{
		if (Token == expectedtoken)
		{
			LexNext ();
			return true;
		}
		return false;
	}

	bool FindClose (const std::string &open, const std::string &close);

	std::string GetTextIn (const std::string &open, const std::string &close);

	
};

}}