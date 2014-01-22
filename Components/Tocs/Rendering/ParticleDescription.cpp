#include "ParticleDescription.h"

namespace Tocs {
namespace Rendering {

ParticleDescription::ParticleDescription()
{
	AddVariable("Position", Graphics::ShaderVariableType::Vector3);
	AddVariable("Size", Graphics::ShaderVariableType::Vector2);
	AddVariable("Rotation", Graphics::ShaderVariableType::Float);
	AddVariable("Life", Graphics::ShaderVariableType::Float);
}

void ParticleDescription::AddVariable(const std::string &name, Graphics::ShaderVariableType type)
{
	Variables.push_back(Variable(name, type,TotalSize));
	TotalSize += type.SizeInBytes();
}


}}