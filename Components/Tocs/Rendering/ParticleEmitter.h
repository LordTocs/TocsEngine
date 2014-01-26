#pragma once
#include <memory>
#include "ParticleDataBuffer.h"

namespace Tocs {
namespace Rendering {

class EmitterValue
{
	class IInternalValue
	{
	public:
		virtual ~IInternalValue() {}

		virtual void Apply(unsigned char *data) = 0;
	};

	template <class T>
	class InternalRange : public IInternalValue
	{
	public:
		T Begin;
		T End;
		InternalRange(T begin, T end)
			: Begin(begin), End(end) {}

		void Apply(unsigned char *data)
		{

		}
	};

	template <class T>
	class InternalValue
	{
	public:
		T Value;

		void Apply(unsigned char *data)
		{
			(*reinterpret_cast<T *> (data)) = Value;
		}
	};

	std::unique_ptr<IInternalValue> Internal;
public:
	void Apply(unsigned char *data) { Internal->Apply(data); }

	template<class T>
	void Range(T begin, T end)
	{ Internal.reset(new InternalRange<T>(begin, end));	}

	template <class T>
	void Value(T value)
	{ Internal.reset(new InternalValue<T>(value)); }
};

class ParticleEmitter
{
public:
	virtual ~ParticleEmitter() {}
	virtual void Update(float dt, ParticleDataBuffer &data) = 0;
	virtual void Emit(unsigned int count, ParticleDataBuffer &data) = 0;
};

}}
