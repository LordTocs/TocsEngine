#pragma once
#include "Shader.h"
#include <type_traits>
namespace Tocs {
namespace Graphics {

class UniformMap
{
public:
	class IUniformElement
	{
		IUniformElement (const IUniformElement &);
	public:
		IUniformElement () {}
		virtual ~IUniformElement() {}
		virtual void PassToShader (const std::string &name, Shader &shader) = 0;
	};

	template <class T>
	class UniformElementRef : public IUniformElement
	{
		const T& Value;
		UniformElementRef (const UniformElementRef &);
	public:
		UniformElementRef (const T& value)
			: Value(value) {}

		void PassToShader (const std::string &name, Shader &shader)
		{
			shader[name] = Value;
		}
	};

	template <class T>
	class UniformElementValue : public IUniformElement
	{
		const T Value;
		UniformElementValue (const UniformElementValue &);
	public:
		UniformElementValue (const T& value)
			: Value(value) {}

		void PassToShader (const std::string &name, Shader &shader)
		{
			shader[name] = Value;
		}
	};

	class UniformValue
	{
		std::unique_ptr<IUniformElement> Element;
		std::string Name;

		UniformValue (const UniformValue &);
	public:
		UniformValue (const std::string &name)
			: Name (name)
		{}

		template<class T>
		void Ref (const T& value)
		{
			Element.reset(new UniformElementRef <T> (value));
		}

		template<class T>
		void Value (const T& value)
		{
			Element.reset(new UniformElementValue <T> (value));
		}

		void PassToShader (Shader &shader) const
		{
			if (Element != nullptr)
			{
				Element->PassToShader (Name,shader);
			}
		}
	};
private:
	std::map<std::string,std::unique_ptr<UniformValue>> Values;

	UniformMap (const UniformMap &);
public:
	UniformMap () {}

	UniformValue &operator[] (const std::string &name)
	{
		auto i = Values.find (name);
		if (i == Values.end())
		{
			i = Values.insert(std::make_pair(name,new UniformValue(name))).first;
		}
		return *i->second;
	}

	void PassToShader (Shader &shader) const
	{
		for (auto i = Values.begin (); i != Values.end (); ++i)
		{
			(*i).second->PassToShader (shader);
		}
	}



};

}}