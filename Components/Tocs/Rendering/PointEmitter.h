#pragma once
#include <random>
#include <string>
#include <utility>
#include "ParticleEmitter.h"
#include <Tocs/Core/Tokenizer.h>

namespace Tocs {
namespace Rendering {
		
class PointEmitter : public ParticleEmitter
{
	std::vector<EmitterValue> Values;
	unsigned int PositionOffset;
	float EmitRate;
	float EmitTime;
public:
	friend class ParamParser;
	friend class RangeParser;

	PointEmitter(const ParticleDescription &desc);
	PointEmitter(PointEmitter &&moveme);

	void Update(float dt, ParticleDataBuffer &data);
	void Emit(unsigned int count, ParticleDataBuffer &data);

	static PointEmitter Parse(const ParticleDescription &desc, Lexing::Tokenizer &tokens);

	ParticleEmitter *Clone() const;
};

}}