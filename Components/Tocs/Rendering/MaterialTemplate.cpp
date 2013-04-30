#include "MaterialTemplate.h"
#include "MaterialValue.h"
#include <Tocs/Graphics/ShaderTypes.h>
#include <sstream>

using namespace std;
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

//Segments///
std::string MaterialTemplate::VariableSegment::GetSegmentText (const MaterialTemplate &matemplate, const MaterialValueSet &valueset) const
{
	stringstream result;
	
	if (valueset.Values[Slot.Index()].MatValue == nullptr)
		return "";
	result << valueset.Values[Slot.Index()].MatValue->GetVariableDeclaration (matemplate) << endl;
	
	return result.str();
}

std::string MaterialTemplate::IfIsSegment::GetSegmentText (const MaterialTemplate &matemplate, const MaterialValueSet &valueset) const
{
	if (valueset[Identifier].MatValue.get () == nullptr)
	{
		if (TargetType == "None")
			return Content;
		else
			return "";
	}

	if (valueset[Identifier].MatValue->GetTypeName() == TargetType)
	{
		return Content;
	}
	return "";
}

std::string MaterialTemplate::InitSegment::GetSegmentText (const MaterialTemplate &matemplate, const MaterialValueSet &valueset) const
{
	stringstream result;
	for (auto i = valueset.Values.begin (); i != valueset.Values.end (); ++i)
	{
		if ((*i).MatValue == nullptr)
			continue;
		result << (*i).MatValue->GetInitialization (matemplate) << endl;
	}
	return result.str();
}

std::string MaterialTemplate::DefSegment::GetSegmentText (const MaterialTemplate &matemplate, const MaterialValueSet &valueset) const
{
	stringstream result;
	for (auto i = valueset.Values.begin (); i != valueset.Values.end (); ++i)
	{
		if ((*i).MatValue == nullptr)
			continue;
		result << (*i).MatValue->GetExtraDefinitions (matemplate) << endl;
	}
	return result.str();
}

std::string MaterialTemplate::GetSource (const MaterialValueSet &values) const
{
	stringstream ss;
	for (auto i = Segments.begin (); i != Segments.end (); ++i)
	{
		ss << (*i)->GetSegmentText (*this,values);
	}
	return ss.str ();
}

MaterialTemplate::MaterialTemplate (MaterialTemplate &&moveme)
	: Segments(std::move(moveme.Segments)),
	  GeneratedCode(std::move(moveme.GeneratedCode)),
	  ValueSlots(std::move(moveme.ValueSlots))
{
}

MaterialTemplate MaterialTemplate::LoadFromFile (const std::string &filename)
{
	stringstream ss;
	StringSource source = StringSource::FromFile (filename);

	MaterialTemplate result;

	while (!source.EndOfSource ())
	{
		auto interupt = GetNextInterupt(source);
		if (interupt.PlainText.size () > 0)
		{
			result.Segments.push_back (unique_ptr<Segment> (new StaticSegment (interupt.PlainText)));
		}

		if (interupt.InteruptText.length () <= 0)
			break;

		StringSource interuptsource(interupt.InteruptText);
		Tokenizer tokens (interuptsource);
		string first = tokens.GetToken ();

		if (first == "definitions")
		{
			result.Segments.push_back (unique_ptr<Segment> (new DefSegment ()));
		}
		else if (first == "initialization")
		{
			result.Segments.push_back (unique_ptr<Segment> (new InitSegment ()));
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

			result.Segments.push_back (unique_ptr<Segment> (new IfIsSegment (ident,type,ifcontent.PlainText)));
		}
		else
		{
			Graphics::ShaderVariableType type = Graphics::ShaderVariableType::FromGLSLTypeString (first);
			string name = tokens.GetToken ();

			VariableSegment *seg = new VariableSegment (name,type,result.ValueSlots.size());
			result.Segments.push_back (unique_ptr<Segment> (seg));
			result.ValueSlots.push_back(&seg->Slot);
		}
	}

	if (ss.str ().length () != 0)
		result.Segments.push_back (unique_ptr<Segment> (new StaticSegment (ss.str ())));

	return std::move(result);
}

const Graphics::ShaderCode &MaterialTemplate::GetShader (const MaterialValueSet &values) const
{
	unsigned int sethash = values.GetHash ();
	auto resultshader = GeneratedCode.find (sethash);
	if (resultshader == GeneratedCode.end ())
	{
		//Create new shader.
		std::unique_ptr<Graphics::ShaderCode> newshader (new Graphics::ShaderCode (Graphics::ShaderType::Pixel));
		
		newshader.get()->Compile (GetSource (values));

		if (!newshader.get()->Compiled ())
		{
			std::cout << "Failed to compile material template: " << std::endl
				      << newshader.get()->GetCompileErrors () << std::endl;

			//errors. throw exception.
		}

		resultshader = const_cast<std::map<unsigned int, std::unique_ptr<Graphics::ShaderCode>> &> (GeneratedCode).insert (std::make_pair(sethash,std::move(newshader))).first;
	}

	return *((*resultshader).second);
}



}}