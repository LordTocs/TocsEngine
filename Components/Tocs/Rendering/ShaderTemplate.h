#pragma once
#include <string>
#include <vector>
#include "PermutationID.h"
#include "PermutationField.h"
#include <Tocs/Core/Tokenizer.h>


namespace Tocs {
namespace Rendering {
namespace Permutations {

class ShaderTemplate
{
	class Segment
	{
	public:
		virtual std::string GetSegmentText (const PermutationID &ID, const ShaderTemplate &temp) const = 0;
		virtual ~Segment () {}
	};

	class StaticSegment : public Segment
	{
		std::string Text;
	public:
		StaticSegment (const std::string &str)
			: Text(str)
		{
		}

		std::string GetSegmentText (const PermutationID &ID, const ShaderTemplate &temp) const
		{
			return Text;
		}
	};

	class VariableSegment : public Segment
	{
		PermutationField Field;
	public:
		VariableSegment(const std::string &name, const Graphics::ShaderVariableType &type)
			: Field (name,type)
		{
		}

		std::string GetSegmentText (const PermutationID &id, const ShaderTemplate &temp) const;
		const std::string &GetName () const { return Field.GetName (); }
	};

	class InitSegment : public Segment
	{
		std::vector<std::string> Strings;
	public:
		std::string GetSegmentText (const PermutationID &id, const ShaderTemplate &temp) const;
	};

	class DefSegment : public Segment
	{
		std::vector<std::string> Strings;
	public:
		std::string GetSegmentText (const PermutationID &id, const ShaderTemplate &temp) const;
		void AddString (const std::string &str) { Strings.push_back(str); }
	};

	class IfIsSegment: public Segment
	{
		std::string Identifier;
		PermutationValueType Type;
		std::string Content;
	public:
		IfIsSegment(std::string ident, PermutationValueType type, std::string content)
			: Identifier(ident), Type(type), Content(content)
		{}
		std::string GetSegmentText (const PermutationID &id, const ShaderTemplate &temp) const;
	};

	
	std::vector<std::unique_ptr<Segment>> Segments;
public:
	std::map<std::string, Permutations::PermutationField> Fields;

	ShaderTemplate(const std::string &filename);
	ShaderTemplate(ShaderTemplate &&moveme);


	std::string GetScript (const PermutationID &id) const;
};

}}}