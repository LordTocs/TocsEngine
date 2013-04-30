#pragma once
#include <vector>
#include <map>
#include "MaterialValueSlot.h"
#include <Tocs/Graphics/Shader.h>
#include <Tocs/Core/Tokenizer.h>
#include "Pipeline.h"

namespace Tocs {
namespace Rendering {

class MaterialValueSet;

class MaterialTemplate
{
	class Segment
	{
	public:
		virtual ~Segment () {}
		virtual std::string GetSegmentText (const MaterialTemplate &matemplate, const MaterialValueSet &valueset) const = 0;
	};

	class StaticSegment : public Segment
	{
		std::string Text;
	public:
		explicit StaticSegment (const std::string &str)
			: Text(str)	{}

		std::string GetSegmentText (const MaterialTemplate &matemplate, const MaterialValueSet &valueset) const	{ return Text; }
		
	};

	class VariableSegment : public Segment
	{
	public:
		MaterialValueSlot Slot;
		VariableSegment(const std::string &name, const Graphics::ShaderVariableType &type, unsigned int index)
			: Slot(name,type,index) {}

		std::string GetSegmentText (const MaterialTemplate &matemplate, const MaterialValueSet &valueset) const;
	};

	class InitSegment : public Segment
	{
	public:
		std::string GetSegmentText (const MaterialTemplate &matemplate, const MaterialValueSet &valueset) const;
	};

	class DefSegment : public Segment
	{
	public:
		std::string GetSegmentText (const MaterialTemplate &matemplate, const MaterialValueSet &valueset) const;
	};

	class IfIsSegment: public Segment
	{
		std::string Identifier;
		std::string TargetType;
		std::string Content;
	public:
		IfIsSegment(const std::string &identifier, const std::string &targettype, const std::string &content)
			: Identifier(identifier),
		      TargetType(targettype),
			  Content (content) 
		{}

		std::string GetSegmentText (const MaterialTemplate &matemplate, const MaterialValueSet &valueset) const;
	};

	
	std::vector<std::unique_ptr<Segment>> Segments;
	std::map<unsigned int, std::unique_ptr<Graphics::ShaderCode>> GeneratedCode;
	std::vector<MaterialValueSlot *> ValueSlots;

	std::string GetSource (const MaterialValueSet &values) const;

	MaterialTemplate (const MaterialTemplate &);
	MaterialTemplate () {}
public:
	MaterialTemplate (MaterialTemplate &&moveme);

	int SlotCount () const { return ValueSlots.size (); }
	MaterialValueSlot &GetSlot (unsigned int index) { return *ValueSlots[index]; }
	const MaterialValueSlot &GetSlot (unsigned int index) const { return *ValueSlots[index]; }

	static MaterialTemplate LoadFromFile (const std::string &filename);

	const Graphics::ShaderCode &GetShader (const MaterialValueSet &values) const;
};

}}
