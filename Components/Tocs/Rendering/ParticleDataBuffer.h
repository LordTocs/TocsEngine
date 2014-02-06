#pragma once
#include "ParticleDescription.h"
#include <Tocs/Graphics/Buffer.h>
namespace Tocs {
namespace Rendering {

class ParticleDataBuffer
{
	const ParticleDescription *Description;
	unsigned int LifeOffset;
	unsigned int MaxParticles;
	bool IsAlive(unsigned char *particle);
public:
	Graphics::BufferBase Data;
	unsigned int ActiveParticles;
	
	ParticleDataBuffer(const ParticleDescription &description, unsigned int count);
	ParticleDataBuffer(ParticleDataBuffer &&moveme);

	ParticleDataBuffer(const ParticleDataBuffer &) = delete;
	ParticleDataBuffer &operator= (const ParticleDataBuffer &) = delete;

	unsigned int MaxParticleCount() const { return MaxParticles; }

	const ParticleDescription &GetDescription() const { return *Description; }

	void Organize();
};

}}