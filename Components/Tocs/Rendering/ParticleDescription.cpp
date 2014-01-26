#include "ParticleDescription.h"

namespace Tocs {
namespace Rendering {

ParticleDescription::ParticleDescription()
{
	AddVariable("Position", Graphics::GPUType::Vector3);
	AddVariable("Size", Graphics::GPUType::Vector2);
	AddVariable("Rotation", Graphics::GPUType::Float);
	AddVariable("Life", Graphics::GPUType::Float);
}

void ParticleDescription::AddVariable(const std::string &name, Graphics::GPUType type)
{
	Variables.push_back(Variable(name, type,TotalSize));
	TotalSize += type.SizeInBytes();
}


}}