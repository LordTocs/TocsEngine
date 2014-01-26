#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Core/LateStatic.h>
#include <Tocs/Graphics/Buffer.h>
#include <Tocs/Graphics/VertexFormat.h>
#include <Tocs/Graphics/ShaderTypes.h>
#include <Tocs/Math/Transform.h>
#include "Vertices.h"
#include "Drawable.h"
#include "Material.h"

#include "ParticleGeometry.h"
#include "ParticleEmitter.h"
#include "ParticleController.h"
#include <random>
namespace Tocs {
namespace Rendering {



class ParticleSystemSource
{
	ParticleDescription Description;

public:

	ParticleController *GetController() const;
	ParticleEmitter *GetEmitter() const;

};

class ParticleSystem : public Drawable
{
	NullableAsset<ParticleSystemSource> Source;
	std::unique_ptr<ParticleController> Controller;
	std::unique_ptr<ParticleEmitter> Emitter;
	ParticleGeometry Particles;
public:
	ParticleSystem(RenderSystem &system, const Asset<ParticleSystemSource> &source);
	ParticleSystem(ParticleSystem &&moveme);

	ParticleSystem(const ParticleSystem &) = delete;
	ParticleSystem &operator= (const ParticleSystem &) = delete;

	void QueueJobs();
	void DeQueueJobs();

	void Update(float dt);
};

}}