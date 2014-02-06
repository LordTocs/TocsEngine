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
	NullableAsset<MaterialSource> ParticleMaterial;
	std::unique_ptr<ParticleEmitter> Emitter;
	std::unique_ptr<ParticleController> Controller;
	unsigned int MaxParticles;
public:
	ParticleSystemSource() : MaxParticles() {}
	ParticleSystemSource(const ParticleSystemSource &) = delete;
	ParticleSystemSource(ParticleSystemSource &&moveme);

	const ParticleDescription &GetDescription() const { return Description; }
	unsigned int GetMaxParticles() const { return MaxParticles; }

	Asset<MaterialSource> GetMaterialSource() const { return ParticleMaterial; }

	ParticleController *GetController() const { return Controller->Clone(); }
	ParticleEmitter *GetEmitter() const { return Emitter->Clone(); }

	static ParticleSystemSource LoadFromFile(const std::string &filename);

};

class ParticleSystem : public Drawable
{
	NullableAsset<ParticleSystemSource> Source;
	std::unique_ptr<ParticleController> Controller;
	std::unique_ptr<ParticleEmitter> Emitter;

	ParticleGeometry Particles;
	Material ParticleMaterial;
public:
	ParticleSystem(RenderSystem &system, const Asset<ParticleSystemSource> &source);
	ParticleSystem(ParticleSystem &&moveme);

	ParticleSystem(const ParticleSystem &) = delete;
	ParticleSystem &operator= (const ParticleSystem &) = delete;

	void QueueJobs();
	void DeQueueJobs();

	void Update(float dt);

	Math::Transform &Transform() { return Emitter->Transform; }
	const Math::Transform &Transform() const { return Emitter->Transform; }
};

}}