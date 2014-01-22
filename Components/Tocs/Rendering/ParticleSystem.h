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
#include <random>
namespace Tocs {
namespace Rendering {



class ParticleSystemSource
{
	unsigned int MaxParticleCount;
	MaterialSource ParticleMaterial;
	unsigned int WorkGroupSize;
private:

	ParticleSystemSource();
public:
	ParticleSystemSource(ParticleSystemSource &&moveme);
	ParticleSystemSource(const ParticleSystemSource&) = delete;

	static ParticleSystemSource LoadFromFile(const std::string &filename);

	unsigned int ParticleCount() const { return MaxParticleCount;  }

//	Graphics::Shader &ParticleShader() { return UpdateShader; }
//	const Graphics::Shader &ParticleShader() const { return UpdateShader; }

	void GenerateVertexShader();
	void GenerateUpdateShader(const std::string &updatefunc);
};

class ParticleSystemGeometry : public Geometry
{
	static Graphics::Buffer<PositionTexture> CreateVertQuadBuffer();
	static FirstUseStatic<Graphics::Buffer<PositionTexture>, CreateVertQuadBuffer> QuadVertexBuffer;
	static Graphics::Buffer<unsigned short> CreateQuadIndexBuffer();
	static FirstUseStatic<Graphics::Buffer<unsigned short>, CreateQuadIndexBuffer> QuadIndexBuffer;
	Graphics::VAO VertexArray;
public:
	DrawCall GetCall() const;

	void LinkShaders(ShaderConstruction &construction, bool HasVertexComponent) const;

	void AddShaderInputs(Graphics::ShaderInput &input) const;

};

class ParticleSystem : public Drawable
{
	static std::mt19937 SetupRandom();
	static FirstUseStatic <std::mt19937,SetupRandom> Engine;

	Asset<ParticleSystemSource> Source;
	
	Math::Transform Transform;
	Graphics::BufferBase ParticleDataBuffer;
	int ActiveParticles;
	
	float TotalLife;
	std::uniform_real_distribution<float> LifeDistribution;
	void EmitParticles(int num);
	void FormatNewParticle(unsigned char *dataptr);
	void CollateParticles();
public:
	ParticleSystem(RenderSystem &system, const Asset<ParticleSystemSource> &source);

	void QueueJobs();
	void DeQueueJobs();

	void Update(float dt);
};

}}