#pragma once

namespace Tocs {

class Character
{
public:
	static bool IsWhiteSpace (char c) { return c == ' ' || c == '\n' || c == '\t' || c == '\r'; }
	static bool IsNumber (char c) { return c >= '0' && c <= '9'; }
	static bool IsLetter (char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
};

}