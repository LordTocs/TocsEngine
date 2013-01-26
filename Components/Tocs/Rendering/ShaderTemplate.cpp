#include "ShaderTemplate.h"
#include <sstream>
using namespace std;
using namespace Tocs::Lexing;
using namespace Tocs::Graphics;
namespace Tocs {
namespace Rendering {
namespace Permutations {

std::string ShaderTemplate::VariableSegment::GetSegmentText (const PermutationID &id, const ShaderTemplate &temp) const
{
	stringstream ss;
	const PermutationID::ValueInfo &info = id[Field.GetName()];
	if (info.Type == PermutationValueType::Constant)
	{
		ss << "uniform " << Field.GetType().ToGLSLTypeString () << " " << Field.GetName() << ";" << endl;
	}

	return ss.str ();
}

std::string ShaderTemplate::DefSegment::GetSegmentText (const PermutationID &id, const ShaderTemplate &temp) const
{
	stringstream ss;

	for (int i = 0; i < id.GetTextureCount (); ++i)
	{
		ss << "uniform sampler2D Texture" << i << ";" << endl;
	}

	return ss.str ();
}

std::string ShaderTemplate::InitSegment::GetSegmentText (const PermutationID &id,const ShaderTemplate &temp) const
{
	stringstream ss;

	for (int i = 0; i < id.GetTextureCount (); ++i)
	{
		ss << "vec4 Sample" << i << " = texture2D(Texture" << i << ", TextureCoordinate);" << endl;
	}

	for (auto i = temp.Fields.begin (); i != temp.Fields.end (); ++i)
	{
		auto info = id[(*i).second.GetName ()];

		if (info.Type == PermutationValueType::Map)
		{
			ss << info.VarType.ToGLSLTypeString () << " " << (*i).second.GetName () << " = Sample" << info.TextureIndex;
			
			string swizzle = ShaderVariableType::GetTruncationSwizzle (ShaderVariableType::Vector4,info.VarType);
			if (swizzle.length () != 0);
				ss << "." << swizzle;
			
			ss << ";" << endl;
		}
		else if (info.Type == PermutationValueType::MapComponent)
		{
			ss << info.VarType.ToGLSLTypeString () << " " << (*i).second.GetName ()  << " = Sample" << info.TextureIndex << "." << info.Component << ";" << endl;
		}
	}
	return ss.str ();
}

std::string ShaderTemplate::IfIsSegment::GetSegmentText (const PermutationID &id, const ShaderTemplate &temp) const
{
	if (id[Identifier].Type == Type)
		return Content;
	return "";
}

class StreamInterupt
{
public:
	std::string PlainText;
	std::string InteruptText;
	StreamInterupt(std::string p, std::string i)
		: PlainText(p), InteruptText(i)
	{}
};

static StreamInterupt GetNextInterupt (StringSource &source)
{
	stringstream plainstream;
	StreamInterupt result ("","");
	while (!source.EndOfSource ())
	{
		char c = source.GetChar ();
		if (c == '<')
		{
			if (source.EndOfSource ())
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
	result.PlainText = plainstream.str ();
	if (source.EndOfSource ())
		return result;

	source.GetChar ();
	
	stringstream escapedtext;

	while (!source.EndOfSource ())
	{
		char c = source.GetChar ();
		if (c == '%')
		{
			if (source.EndOfSource ())
				return result;
			if (source.PeekChar () == '>')
			{
				source.GetChar ();
				result.InteruptText = escapedtext.str ();
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
ShaderTemplate::ShaderTemplate(const std::string &filename)
{
	stringstream ss;
	StringSource source = StringSource::FromFile (filename);

	while (!source.EndOfSource ())
	{
		auto interupt = GetNextInterupt(source);

		Segments.push_back (unique_ptr<Segment> (new StaticSegment (interupt.PlainText)));

		if (interupt.InteruptText.length () <= 0)
			break;

		StringSource interuptsource(interupt.InteruptText);
		Tokenizer tokens (interuptsource);
		string first = tokens.GetToken ();

		if (first == "definitions")
		{
			Segments.push_back (unique_ptr<Segment> (new DefSegment ()));
		}
		else if (first == "initialization")
		{
			Segments.push_back (unique_ptr<Segment> (new InitSegment ()));
		}
		else if (first == "ifis")
		{
			string ident = tokens.GetToken ();
			tokens.GetToken (); // ':'
			string type = tokens.GetToken ();

			auto ifcontent = GetNextInterupt(source);
			if (ifcontent.InteruptText != "endif")
			{
				//ERROR
			}

			//MAKE THE IFSTATEMENT DAMN YOU
			Segments.push_back (unique_ptr<Segment> (new IfIsSegment (ident,PermutationValueType::FromString(type),ifcontent.PlainText)));
		}
		else
		{
			ShaderVariableType type = ShaderVariableType::FromGLSLTypeString (first);
			string name = tokens.GetToken ();

			Fields[name] = PermutationField (name,type);
			Segments.push_back (unique_ptr<Segment> (new VariableSegment (name,type)));
		}
	}

	if (ss.str ().length () != 0)
		Segments.push_back (unique_ptr<Segment> (new StaticSegment (ss.str ())));
}

ShaderTemplate::ShaderTemplate (ShaderTemplate &&moveme)
	: Fields (std::move(moveme.Fields)),
	  Segments (std::move(moveme.Segments))
{}

std::string ShaderTemplate::GetScript (const PermutationID &id) const
{
	stringstream ss;
	for (auto i = Segments.begin (); i != Segments.end (); ++i)
	{
		ss << (*i)->GetSegmentText (id,*this);
	}
	return ss.str ();
}


}}}