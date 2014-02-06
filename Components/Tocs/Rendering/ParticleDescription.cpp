#include "ParticleDescription.h"
#include <algorithm>
#include <sstream>
namespace Tocs {
namespace Rendering {

ParticleDescription::ParticleDescription()
: TotalSize(0)
{
	AddVariable("Position", Graphics::GPUType::Vector3);
	AddVariable("Size", Graphics::GPUType::Vector2);
	AddVariable("Rotation", Graphics::GPUType::Float);
	AddVariable("Life", Graphics::GPUType::Float);
}

void ParticleDescription::AddVariable(const std::string &name, Graphics::GPUType type)
{
	unsigned int pos = TotalSize;
	unsigned int alignment = type.Std140BaseAlignment();
	unsigned int padding = (pos % alignment);
	if (padding != 0)
	{
		padding = alignment - padding;
	}
	pos += padding;
	TotalSize += padding;
	Variables.push_back(Variable(name, type, pos));
	TotalSize += type.SizeInBytes();
}

void ParticleDescription::CalculatePadding()
{
	unsigned int structalignment = Graphics::GPUType::Vector4.Std140BaseAlignment();
	for (auto &v : Variables)
	{
		structalignment = std::max(v.Type().Std140BaseAlignment(), structalignment);
	}
	unsigned int padding = (TotalSize % structalignment);
	if (padding != 0)
	{
		padding = structalignment - padding;
	}
	TotalSize += padding;
}

const ParticleDescription::Variable &ParticleDescription::operator[] (const std::string &name) const
{
	auto i = std::find_if(Variables.begin(), Variables.end(), [&](const Variable &v)->bool{return v.Name() == name;});
	return *i;
}

ParticleDescription ParticleDescription::Parse(Lexing::Tokenizer &tokens)
{
	ParticleDescription result;

	while (!tokens.EndOfStream())
	{
		if (tokens.PeekType() == Lexing::TokenType::Comment)
		{
			tokens.GetToken();
			continue;
		}

		if (tokens.PeekType() != Lexing::TokenType::Word)
		{
			break;
		}

		if (!tokens.Is("var"))
		{
			break;
		}

		if (!tokens.Is(":"))
		{
			break;
		}

		Graphics::GPUType type = Graphics::GPUType::FromTypeString(tokens.GetToken());
		std::string name = tokens.GetToken();
		result.AddVariable(name, type);
	}
	result.CalculatePadding();
	return std::move(result);
}

std::string ParticleDescription::GetGLSLStruct() const
{
	std::stringstream ss;
	ss << "struct Particle" << std::endl << "{" << std::endl;

	for (auto &v : Variables)
	{
		ss << "\t" << v.Type().ToShaderVariable().ToGLSLTypeString() << " " << v.Name() << ";" << std::endl;
	}

	ss << "};" << std::endl;
	return ss.str();
}

}}