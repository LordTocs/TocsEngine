#pragma once
#include <memory>
#include <random>
#include <vector>
#include <type_traits>
#include <Tocs/Math/Vector.h>
#include <Tocs/Core/LateStatic.h>
#include <Tocs/Math/Transform.h>
#include "ParticleDescription.h"
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

		virtual IInternalValue *Clone() const = 0;
	};

	template <class T, class Enable = void>
	class InternalRange : public IInternalValue {};

	template <class T>
	class InternalRange <T, typename std::enable_if<std::is_integral<T>::value>::type> : public IInternalValue
	{
		std::uniform_int_distribution<T> Distribution;
	public:
		InternalRange(T begin, T end_exclusive)
			: Distribution(begin, end_exclusive) {}

		void Apply(unsigned char *data)
		{
			(*reinterpret_cast<T *> (data)) = Distribution(ParticleEmitter::Random.Get());
		}

		IInternalValue *Clone() const
		{
			return new InternalRange(*this);
		}
	};

	template <class T>
	class InternalRange <T, typename std::enable_if<std::is_floating_point<T>::value>::type> : public IInternalValue
	{
		std::uniform_real_distribution<T> Distribution;
	public:
		InternalRange(T begin, T end_exclusive)
			: Distribution(begin, end_exclusive) {}

		void Apply(unsigned char *data)
		{
			(*reinterpret_cast<T *> (data)) = Distribution(ParticleEmitter::Random.Get());
		}

		IInternalValue *Clone() const
		{
			return new InternalRange(*this);
		}
	};

	template <class T, unsigned int N>
	class InternalRange <Math::VectorBase <T, N>, typename std::enable_if<std::is_integral<T>::value>::type> : public IInternalValue
	{
		std::vector<std::uniform_int_distribution<T>> Distributions;
	public:
		InternalRange(Math::VectorBase <T, N> begin, Math::VectorBase <T, N> end_exclusive)
			: Distributions()
		{
			Distributions.reserve(N);
			for (int i = 0; i < N; ++i)
			{
				Distributions.push_back(std::uniform_int_distribution<T>(begin[i], end_exclusive[i]));
			}
		}

		void Apply(unsigned char *data)
		{
			for (int i = 0; i < N; ++i)
			{
				(*reinterpret_cast<Math::VectorBase <T, N> *> (data))[i] = Distributions[i](ParticleEmitter::Random.Get());
			}
		}

		IInternalValue *Clone() const
		{
			return new InternalRange(*this);
		}
	};

	template <class T, unsigned int N>
	class InternalRange <Math::VectorBase <T, N>, typename std::enable_if<std::is_floating_point<T>::value>::type> : public IInternalValue
	{
		std::vector<std::uniform_real_distribution<T>> Distributions;

	public:
		InternalRange(Math::VectorBase <T, N> begin, Math::VectorBase <T, N> end_exclusive)
			: Distributions()
		{
			Distributions.reserve(N);
			for (int i = 0; i < N; ++i)
			{
				Distributions.push_back(std::uniform_real_distribution<T>(begin[i],end_exclusive[i]));
			}
		}

		void Apply(unsigned char *data)
		{
			for (int i = 0; i < N; ++i)
			{
				(*reinterpret_cast<Math::VectorBase <T, N> *> (data))[i] = Distributions[i](ParticleEmitter::Random.Get());
			}
		}

		IInternalValue *Clone() const
		{
			return new InternalRange(*this);
		}
	};



	template <class T>
	class InternalValue : public IInternalValue
	{
	public:
		T Value;

		InternalValue(T value)
			: Value(value) {}

		void Apply(unsigned char *data)
		{
			(*reinterpret_cast<T *> (data)) = Value;
		}

		IInternalValue *Clone() const
		{
			return new InternalValue(*this);
		}
	};

	std::unique_ptr<IInternalValue> Internal;

	unsigned int Offset;
public:
	EmitterValue(const std::string &name, const ParticleDescription &desc) : Offset(desc[name].Offset()) {}
	EmitterValue(const EmitterValue &value)
		: Offset(value.Offset), Internal(value.Internal->Clone()) {}
	void Apply(unsigned char *data);

	template<class T>
	void Range(T begin, T end)
	{
		Internal.reset(new InternalRange<T>(begin, end));
	}

	template <class T>
	void Value(T value)
	{
		Internal.reset(new InternalValue<T>(value));
	}
};

class ParticleEmitter
{
public:
	static std::mt19937 InitRandom();
	static FirstUseStatic<std::mt19937, InitRandom> Random;

	Math::Transform Transform;
	virtual ~ParticleEmitter() {}
	virtual void Update(float dt, ParticleDataBuffer &data) = 0;
	virtual void Emit(unsigned int count, ParticleDataBuffer &data) = 0;
	virtual ParticleEmitter *Clone () const = 0;
};

}}
