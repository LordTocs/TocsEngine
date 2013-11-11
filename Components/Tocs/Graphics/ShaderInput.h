#pragma once
#include "Shader.h"
#include "UniformMap.h"

namespace Tocs {
namespace Graphics {

class ShaderInput
{
	

	class IUniformElement
	{
		IUniformElement (const IUniformElement &);
	protected:
		ShaderUniform &Uniform;
	public:
		IUniformElement (ShaderUniform &uniform) : Uniform(uniform) {}
		virtual ~IUniformElement() {}
		virtual void PassToShader() = 0;
	};

	template <class T>
	class UniformElementRef : public IUniformElement
	{
		const T& Value;
		UniformElementRef (const UniformElementRef &);
	public:
		UniformElementRef (const T& value, ShaderUniform &uniform)
			: Value(value), IUniformElement(uniform) {}

		void PassToShader ()
		{
			Uniform = Value;
		}
	};

	template <class T>
	class UniformElementValue : public IUniformElement
	{
		const T Value;
		UniformElementValue (const UniformElementValue &);
	public:
		UniformElementValue (const T& value, ShaderUniform &uniform)
			: Value(value), IUniformElement(uniform) {}

		void PassToShader ()
		{
			Uniform = Value;
		}
	};

	class UniformMapReference : public IUniformElement
	{
		const UniformMap::UniformValue *Value;
	public:
		UniformMapReference (const UniformMap::UniformValue *value, ShaderUniform &uniform)
			: Value (value),  IUniformElement(uniform) {}

		void PassToShader ()
		{
			Value->PassToUniform(Uniform);
		}
	};

public:
	class UniformValue
	{
		std::unique_ptr<IUniformElement> Element;
		ShaderUniform &Uniform;
		UniformValue (const UniformValue &);
	public:
		UniformValue (ShaderUniform &uniform)
			: Uniform(uniform) {}

		template<class T>
		void Ref (const T& value)
		{
			Element.reset(new UniformElementRef <T> (value,Uniform));
		}

		template<class T>
		void Value (const T& value)
		{
			Element.reset(new UniformElementValue <T> (value, Uniform));
		}

		void MapReference (const UniformMap::UniformValue *value)
		{
			Element.reset(new UniformMapReference (value, Uniform));
		}

		void PassToShader () const
		{
			if (Element != nullptr)
			{
				Element->PassToShader ();
			}
		}
	};
private:
	Shader *TargetShader;

	std::map<std::string,std::unique_ptr<UniformValue>> Values;

	ShaderInput(const ShaderInput &);
public:
	ShaderInput(Shader &target)
		: TargetShader (&target) {}

	ShaderInput(ShaderInput &&moveme)
		: Values(std::move(moveme.Values)),
		  TargetShader(moveme.TargetShader)
	      {}

	ShaderInput &operator=(ShaderInput &&moveme)
	{
		Values = std::move(moveme.Values);
		TargetShader = moveme.TargetShader;
	}


	UniformValue &operator[] (const std::string &name)
	{
		auto i = Values.find (name);
		if (i == Values.end())
		{
			i = Values.emplace(name,std::make_unique <UniformValue> ((*TargetShader)[name])).first;
		}
		return *i->second;
	}

	void ApplyMap (const UniformMap &map)
	{
		for (auto i = map.Begin (); i != map.End (); ++i)
		{
			(*this)[(*i).first].MapReference((*i).second.get()); //fff need shared_ptr
		}
	}

	void PassToShader () const
	{
		for (auto i = Values.begin (); i != Values.end (); ++i)
		{
			(*i).second->PassToShader ();
		}
	}
};


}}

