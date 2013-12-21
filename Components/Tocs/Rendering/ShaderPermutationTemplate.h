#pragma once
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <Tocs/Graphics/ShaderCode.h>
#include <Tocs/Graphics/ShaderTypes.h>

namespace Tocs {
namespace Rendering {

class PermutationParameter
{
public:
	Graphics::ShaderVariableType Type;
	std::string Name;
	bool Optional;
	unsigned int SegmentIndex;

	PermutationParameter(Graphics::ShaderVariableType type, const std::string &name, bool optional, unsigned int index)
		: Type(type), Name(name), Optional(optional), SegmentIndex(index) {}

	bool operator< (const PermutationParameter &op2)
	{
		return Name < op2.Name;
	}
};

class ShaderPermutationInput;

class ShaderPermutationTemplate
{
public:
	class Segment
	{
	public:
		virtual ~Segment(){}
		virtual std::string GetSegmentText(const ShaderPermutationTemplate &temp, const ShaderPermutationInput &) = 0;
	};
private:
	std::vector<std::unique_ptr<Segment>> Segments;
	std::vector<PermutationParameter> Parameters;
	ShaderPermutationTemplate() : ShaderType(Graphics::ShaderType::Pixel) {}

	std::map <unsigned int, Graphics::ShaderCode> CompiledCodeCache;

	Graphics::ShaderType ShaderType;
public:
	ShaderPermutationTemplate(ShaderPermutationTemplate &&moveme)
		: Parameters(std::move(moveme.Parameters)), Segments(std::move(moveme.Segments)), ShaderType(moveme.ShaderType){}

	static ShaderPermutationTemplate LoadFromFile(const std::string &filename);
	static ShaderPermutationTemplate ParseFromString(const std::string &source);

	std::vector<PermutationParameter>::const_iterator Begin() const { return Parameters.begin(); }
	std::vector<PermutationParameter>::const_iterator End() const { return Parameters.end(); }

	std::string GenerateShaderCode(const ShaderPermutationInput &input) const;

	const Graphics::ShaderCode &GetShaderCode(const ShaderPermutationInput &input) const; //possibly const with const_cast

};




}}