#include "ParticleDataBuffer.h"

namespace Tocs {
namespace Rendering {

ParticleDataBuffer::ParticleDataBuffer(const ParticleDescription &description, unsigned int count)
: Data(count * description.ParticleDataSize()), Description(&description)
{

}

}
}