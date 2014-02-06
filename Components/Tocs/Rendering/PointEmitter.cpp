#include "PointEmitter.h"
#include <Tocs/Core/Float.h>
#include <Tocs/Core/Integer.h>
#include <Tocs/Math/ConstantParser.h>
namespace Tocs {
namespace Rendering {

PointEmitter::PointEmitter(const ParticleDescription &desc)
: EmitRate(10), EmitTime(0), PositionOffset(0)
{
	PositionOffset = desc["Position"].Offset();

	std::cout << "Description Offsets:" << std::endl;
	for (auto &v : desc.Variables)
	{
		std::cout << v.Name() << " : " << v.Type().ToShaderVariable().ToGLSLTypeString() << " : " << v.Offset() << " (" << v.Type().Std140BaseAlignment() << ")" << std::endl;
	}

}

PointEmitter::PointEmitter(PointEmitter &&moveme)
: EmitRate(moveme.EmitRate), EmitTime(moveme.EmitTime), Values(std::move(moveme.Values)), PositionOffset(moveme.PositionOffset)
{

}

void PointEmitter::Update(float dt, ParticleDataBuffer &data)
{
	EmitTime += dt;
	if (EmitTime > (1.0f / EmitRate))
	{
		Emit(1, data);
		EmitTime = 0;
	}
}

void PointEmitter::Emit(unsigned int count, ParticleDataBuffer &data)
{
	unsigned char *buffer = reinterpret_cast<unsigned char *> (data.Data.Map());
	int end = data.ActiveParticles + count;
	for (int i = data.ActiveParticles; i < end && i < data.MaxParticleCount(); ++i)
	{
		unsigned char *particle =buffer + (data.GetDescription().ParticleDataSize() * i);
		(*reinterpret_cast<Math::Vector3 *>(particle + PositionOffset)) = Transform.GetWorldPosition();
		for (auto &v : Values)
		{
			v.Apply(particle);
		}
		++data.ActiveParticles;
	}
	data.Data.UnMap();
}

ParticleEmitter *PointEmitter::Clone() const
{
	return new PointEmitter(*this);
}
class ParamParser //WHY YOU NO GENERIC LAMBDA?
{
	std::string Param;
	PointEmitter &Emitter;
	const ParticleDescription &Description;
public:
	ParamParser(const std::string &param, PointEmitter &emitter, const ParticleDescription &desc)
		: Param(param), Emitter(emitter),Description(desc) {}
	
	template <class T>
	void operator() (const T &value)
	{
		EmitterValue resultvalue(Param, Description);
		resultvalue.Value(value);
		Emitter.Values.push_back(resultvalue);
	}
};

class RangeParser
{
	std::string Param;
	PointEmitter &Emitter;
	const ParticleDescription &Description;
public:
	class IParsePair
	{
	public:
		virtual ~IParsePair() {}
	};
	template <class T>
	class ParsePair : public IParsePair
	{
	public:
		T A, B;
	};

	std::unique_ptr<IParsePair> Pair;

	RangeParser(const std::string &param, PointEmitter &emitter, const ParticleDescription &desc)
		: Param(param), Emitter(emitter), Description(desc) {}

	template <class T>
	void operator()(const T &value)
	{
		if (Pair == nullptr)
		{
			ParsePair<T> *pair = new ParsePair <T>();
			pair->A = value;
			Pair.reset(pair);
		}
		else
		{
			ParsePair<T> *pair = dynamic_cast<ParsePair<T> *> (Pair.get());
			if (pair != nullptr)
			{
				pair->B = value;
				EmitterValue resultvalue(Param, Description);
				resultvalue.Range(pair->A,pair->B);
				Emitter.Values.push_back(resultvalue);
			}
		}
	}
};
PointEmitter PointEmitter::Parse(const ParticleDescription &desc, Lexing::Tokenizer &tokens)
{
	PointEmitter result(desc);
	while (!tokens.EndOfStream())
	{
		std::string parameter = tokens.GetToken();
		
		if (!tokens.Is(":"))
		{
		}

		if (parameter == "EmitRate")
		{
			result.EmitRate = Float::Parse(tokens.GetToken());
			continue;
		}
		
		
		if (!tokens.Is("range"))
		{
			ParamParser parser(parameter, result, desc);
			if (!Math::ConstantParser::TryParse(tokens, parser))
			{}
		}
		else
		{
			if (!tokens.Is("(")){}
			RangeParser parser(parameter, result, desc);
			if (!Math::ConstantParser::TryParse(tokens, parser)) {}
			if (!tokens.Is(",")){}
			if (!Math::ConstantParser::TryParse(tokens, parser)) {}
			if (!tokens.Is(")")){}
		}
	}
	return std::move(result);
}

}
}

