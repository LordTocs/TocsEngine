#include "ShaderPermutationTemplate.h"
#include "ShaderPermutationInput.h"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cassert>
#include <Tocs/Core/Tokenizer.h>

using namespace Tocs::Lexing;

namespace Tocs {
namespace Rendering {


class StreamInterupt
{
public:
	std::string PlainText;
	std::string InteruptText;
	StreamInterupt(std::string p, std::string i)
		: PlainText(p), InteruptText(i)
	{}
};

static StreamInterupt GetNextInterupt(StringSource &source)
{
	std::stringstream plainstream;
	StreamInterupt result("", "");
	while (!source.EndOfSource())
	{
		char c = source.GetChar();
		if (c == '<')
		{
			if (source.EndOfSource())
				break;
			if (source.PeekChar() == '%')
			{
				break;
			}
		}
		else
		{
			plainstream << c;
		}
	}
	result.PlainText = plainstream.str();
	if (source.EndOfSource())
		return result;

	source.GetChar();

	std::stringstream escapedtext;

	while (!source.EndOfSource())
	{
		char c = source.GetChar();
		if (c == '%')
		{
			if (source.EndOfSource())
				return result;
			if (source.PeekChar() == '>')
			{
				source.GetChar();
				result.InteruptText = escapedtext.str();
				break;
			}
		}
		else
		{
			escapedtext << c;
		}
	}

	return result;
}


class StaticSegment : public ShaderPermutationTemplate::Segment
{
	std::string Code;
public:
	StaticSegment(const std::string &code) : Code(code) {}

	std::string GetSegmentText(const ShaderPermutationTemplate &temp, const ShaderPermutationInput &)
	{ return Code; }
};

class VariableSegment : public ShaderPermutationTemplate::Segment
{
public:
	unsigned int ParameterIndex;

	VariableSegment(unsigned int paramindex)
		: ParameterIndex(paramindex) {}

	std::string GetSegmentText(const ShaderPermutationTemplate &temp, const ShaderPermutationInput &input)
	{
		const auto i = input.GetSlot((temp.Begin() + ParameterIndex)->Name);
		if (i != nullptr)
			return i->Slot->GetVariableDeclaration(temp, ParameterIndex, *i);
		else
		{
			return "";
		}
	}
};

class InitializationSegment : public ShaderPermutationTemplate::Segment
{
public:
	std::string GetSegmentText(const ShaderPermutationTemplate &temp, const ShaderPermutationInput &input)
	{
		std::stringstream result;
		auto p = temp.Begin();
		for (auto i = input.Values.begin(); i != input.Values.end(); ++i)
		{
			while (p != temp.End() && p->Name != i->Name && p->Name < i->Name)
			{
				++p;
			}
			if (p == temp.End())
				break;
			if (p->Name != i->Name)
				continue;

			result << i->Slot->GetInitialization(temp, p - temp.Begin(), *i) << std::endl;
		}
		return result.str();
	}
};

class DefinitionSegment : public ShaderPermutationTemplate::Segment
{
public:
	std::string GetSegmentText(const ShaderPermutationTemplate &temp, const ShaderPermutationInput &input)
	{
		std::stringstream result;
		auto p = temp.Begin();
		for (auto i = input.Values.begin(); i != input.Values.end(); ++i)
		{
			while (p != temp.End() && p->Name != i->Name && p->Name < i->Name)
			{
				++p;
			}
			if (p == temp.End())
				break;
			if (p->Name != i->Name)
				continue;

			result << i->Slot->GetExtraDefinitions(temp, p - temp.Begin(), *i) << std::endl;
		}
		return result.str();
	}
};

class IfIsSegment : public ShaderPermutationTemplate::Segment
{
public:
	std::string Variable;
	std::string TargetType;
	std::string Content;
	bool Not;

	IfIsSegment(const std::string &var, const std::string &type, const std::string &content, bool not)
		: Variable(var), TargetType(type), Content(content), Not(not)
	{
		
	}

	std::string GetSegmentText(const ShaderPermutationTemplate &temp, const ShaderPermutationInput &input)
	{
		auto slot = input.GetSlot(Variable);
		std::string type = "None";
		if (slot != nullptr && slot->Slot.get() != nullptr)
			type = slot->Slot->GetTypeName();

		if (type == TargetType)
		{
			if (!Not)
				return Content;
		}
		else
		{
			if (Not)
				return Content;
		}
		return "";
	}
};


ShaderPermutationTemplate ShaderPermutationTemplate::LoadFromFile(const std::string &filename)
{
	std::ifstream t(filename);

	if (!t.good())
		throw "FFFFF";

	std::string str;

	t.seekg(0, std::ios::end);
	str.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());


	return ParseFromString(str);
}

ShaderPermutationTemplate ShaderPermutationTemplate::ParseFromString(const std::string &source)
{
	StringSource src(source);

	ShaderPermutationTemplate result;

	while (!src.EndOfSource())
	{
		auto interupt = GetNextInterupt(src);
		if (interupt.PlainText.size() > 0)
		{
			result.Segments.emplace_back (new StaticSegment(interupt.PlainText));
		}

		if (interupt.InteruptText.length() <= 0)
			break;

		StringSource interuptsource(interupt.InteruptText);
		Tokenizer tokens(interuptsource);
		std::string first = tokens.GetToken();

		if (first == "input")
		{
			Graphics::ShaderVariableType type = Graphics::ShaderVariableType::FromGLSLTypeString(tokens.GetToken());

			std::string name = tokens.GetToken();

			bool optional = false;
			if (tokens.Is("optional"))
				optional = true;

			result.Parameters.emplace_back(type, name, optional, result.Segments.size());
			result.Segments.emplace_back(new VariableSegment(result.Parameters.size() - 1));
		}
		else if (first == "init")
		{
			result.Segments.emplace_back(new InitializationSegment());
		}
		else if (first == "definitions")
		{
			result.Segments.emplace_back(new DefinitionSegment());
		}
		else if (first == "ifis")
		{
			bool not = tokens.Is("not");
			std::string ident = tokens.GetToken();
			tokens.GetToken(); // ':'
			std::string type = tokens.GetToken();

			auto ifcontent = GetNextInterupt(src);
			if (ifcontent.InteruptText != "endif")
			{ /*ERROR*/ }

			result.Segments.emplace_back(new IfIsSegment(ident, type, ifcontent.PlainText, not));
		}
	}

	
	std::sort(result.Parameters.begin(), result.Parameters.end());
	for (auto i = result.Parameters.begin(); i != result.Parameters.end(); ++i)
	{
		VariableSegment *varseg = dynamic_cast<VariableSegment *> (result.Segments[i->SegmentIndex].get());
		varseg->ParameterIndex = (i - result.Parameters.begin());
	}
	

	return result; 

}

std::string ShaderPermutationTemplate::GenerateShaderCode(const ShaderPermutationInput &input) const
{
	std::stringstream ss;
	for (auto i = Segments.begin(); i != Segments.end(); ++i)
	{
		ss << (*i).get()->GetSegmentText(*this, input);
	}
	return ss.str();
}

const Graphics::ShaderCode &ShaderPermutationTemplate::GetShaderCode(const ShaderPermutationInput &input) const
{
	unsigned int inputhash = input.GetHash(); //This is problematic extra values = different hash and hey what're the chances of a collision?
	auto c = CompiledCodeCache.find(inputhash);
	if (c != CompiledCodeCache.end())
	{
		return c->second;
	} 
	
	Graphics::ShaderCode code(ShaderType);


	std::string shadercode = GenerateShaderCode(input);
	code.Compile(shadercode);

	if (!code.Compiled())
	{
		std::cout << "=====Compile Errors In Generated Shader===" << std::endl << code.GetCompileErrors() << std::endl << std::endl;
		assert(false);
	}
	auto &cache = const_cast<std::map <unsigned int, Graphics::ShaderCode> &> (CompiledCodeCache); //dafuq.
	c = cache.emplace(std::make_pair(inputhash, std::move(code))).first;
	return c->second;
}


}}