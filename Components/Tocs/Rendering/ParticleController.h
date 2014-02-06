#pragma once
#include "ParticleDataBuffer.h"

namespace Tocs {
namespace Rendering {

class RenderSystem;

class ParticleController
{
public:
	virtual ~ParticleController() {}
	virtual void Update(float dt, ParticleDataBuffer &data, RenderSystem &system) = 0;

	virtual ParticleController *Clone() const = 0;
};

}}