#include "ParticleDataBuffer.h"
#include <memory>
namespace Tocs {
namespace Rendering {

ParticleDataBuffer::ParticleDataBuffer(const ParticleDescription &description, unsigned int count)
: Data(count * description.ParticleDataSize()), Description(&description)
{

}


void ParticleDataBuffer::Organize()
{
	unsigned char *buffer = static_cast<unsigned char *> (Data.Map());
	unsigned char *frontptr = buffer;
	unsigned int size = Description->ParticleDataSize();
	unsigned char *backptr = buffer + (-1) * size;
	
	std::unique_ptr<unsigned char[]> tempbuffer(new unsigned char[size]);
	//Iterate to start positions

	while ((*reinterpret_cast<float*> (frontptr + 24)) > 0)
		frontptr += size;
	while ((*reinterpret_cast<float*> (backptr + 24))  < 0)
		backptr -= size;

	while (frontptr < backptr)
	{
		if (((*reinterpret_cast<float*> (frontptr + 24)) < 0) && ((*reinterpret_cast<float*> (backptr + 24))  > 0))
		{
			//Swap the two particles in the buffer
			std::memcpy(tempbuffer.get(), frontptr, size);
			//back to front
			std::memcpy(frontptr, backptr, size);
			//temp to back
			std::memcpy(backptr, tempbuffer.get(), size);

			while ((*reinterpret_cast<float*> (frontptr + 24)) > 0)
				frontptr += size;
			while ((*reinterpret_cast<float*> (backptr + 24))  < 0)
				backptr -= size;
		}
	}

	ActiveParticles = (frontptr - buffer) / size;

	Data.UnMap();
}

}
}