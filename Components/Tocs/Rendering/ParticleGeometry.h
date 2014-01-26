#pragma once
#include <Tocs/Core/LateStatic.h>
#include "Geometry.h"
#include "Vertices.h"
#include "ParticleDescription.h"
#include "ParticleDataBuffer.h"
namespace Tocs {
namespace Rendering {

class ParticleGeometry : public Geometry
{
	static Graphics::Buffer<PositionTexture> CreateVertQuadBuffer();
	static FirstUseStatic<Graphics::Buffer<PositionTexture>, CreateVertQuadBuffer> QuadVertexBuffer;
	static Graphics::Buffer<unsigned short> CreateQuadIndexBuffer();
	static FirstUseStatic<Graphics::Buffer<unsigned short>, CreateQuadIndexBuffer> QuadIndexBuffer;
	Graphics::VAO VertexArray;
	ParticleDataBuffer ParticleData;
public:
	ParticleGeometry(const ParticleDescription &description, unsigned int particlecount);

	DrawCall GetCall() const;

	void LinkShaders(ShaderConstruction &construction, bool HasVertexComponent) const;

	void AddShaderInputs(Graphics::ShaderInput &input) const;

	ParticleDataBuffer &Data() { return ParticleData; }
	const ParticleDataBuffer &Data() const { return ParticleData; }
};

}}