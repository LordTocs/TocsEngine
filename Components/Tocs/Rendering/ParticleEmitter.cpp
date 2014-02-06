#include "ParticleEmitter.h"

namespace Tocs {
namespace Rendering {

void EmitterValue::Apply(unsigned char *data)
{
	data += Offset;

	if (Internal != nullptr)
		Internal->Apply(data);
}

std::mt19937 ParticleEmitter::InitRandom()
{
	std::random_device rand;

	std::mt19937 result(rand());

	return std::move(result);
}
FirstUseStatic<std::mt19937, ParticleEmitter::InitRandom> ParticleEmitter::Random;

}
}