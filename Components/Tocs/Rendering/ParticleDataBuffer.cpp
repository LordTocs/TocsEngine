#include "ParticleDataBuffer.h"
#include <memory>
namespace Tocs {
namespace Rendering {

ParticleDataBuffer::ParticleDataBuffer(const ParticleDescription &description, unsigned int count)
: Data(count * description.ParticleDataSize())
, Description(&description)
, ActiveParticles(0)
, LifeOffset(description["Life"].Offset())
, MaxParticles(count)
{

}

ParticleDataBuffer::ParticleDataBuffer(ParticleDataBuffer &&moveme)
: Data(std::move(moveme.Data))
, Description(std::move(moveme.Description))
, ActiveParticles(moveme.ActiveParticles)
, LifeOffset(moveme.LifeOffset)
, MaxParticles(moveme.MaxParticles)
{

}
bool ParticleDataBuffer::IsAlive(unsigned char *particle)
{
	return (*reinterpret_cast<float*> (particle + LifeOffset)) > 0;
}

void ParticleDataBuffer::Organize()
{
	unsigned char *buffer = static_cast<unsigned char *> (Data.Map());
	unsigned char *frontptr = buffer;
	unsigned int size = Description->ParticleDataSize();
	unsigned char *backptr = buffer + (MaxParticles-1) * size;
	
	std::unique_ptr<unsigned char[]> tempbuffer(new unsigned char[size]);
	//Iterate to start positions

	while (IsAlive(frontptr))
		frontptr += size;
	while (!IsAlive(backptr))
		backptr -= size;

	while (frontptr < backptr)
	{
		if (!IsAlive(frontptr) && IsAlive(backptr))
		{
			//Swap the two particles in the buffer
			std::memcpy(tempbuffer.get(), frontptr, size);
			//back to front
			std::memcpy(frontptr, backptr, size);
			//temp to back
			std::memcpy(backptr, tempbuffer.get(), size);

			while (IsAlive(frontptr))
				frontptr += size;
			while (!IsAlive(backptr))
				backptr -= size;
		}
	}

	ActiveParticles = (frontptr - buffer) / size;

	Data.UnMap();
}

}
}