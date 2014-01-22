#pragma once
#include "ParticleDataBuffer.h"
namespace Tocs {
namespace Rendering {

class ParticleController
{
public:
	virtual ~ParticleController() {}
	virtual void Update(float dt, ParticleDataBuffer &data) = 0;
};

}}