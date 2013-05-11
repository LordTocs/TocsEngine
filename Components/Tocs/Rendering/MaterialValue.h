#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/ShaderTypes.h>
#include <Tocs/Graphics/Texture.h>
#include <Tocs/Graphics/UniformMap.h>
#include <sstream>

#include "MaterialTemplate.h"

namespace Tocs {
namespace Rendering {

class MaterialValue
{
public:
	MaterialValue ()
		: ValueIndex(0),ResourceIndex(0) {}

	virtual ~MaterialValue() {}

	virtual void Update (float dt) {}

	virtual unsigned int GetResourceHash () const { return 0; }
	virtual unsigned int GetType () const = 0;
	virtual std::string GetTypeName () const = 0;

	virtual std::string GetVariableDeclaration (const MaterialTemplate &matemplate) const { return ""; }
	virtual std::string GetInitialization (const MaterialTemplate &matemplate) const { return ""; }
	virtual std::string GetExtraDefinitions (const MaterialTemplate &matemplate) const { return ""; }

	unsigned int ValueIndex;
	unsigned int ResourceIndex;

	virtual void PassToShader (Graphics::Shader &shader, const MaterialTemplate &matemplate) const = 0;
	virtual void PassToUniformMap (Graphics::UniformMap &map, const MaterialTemplate &matemplate) const = 0;

	virtual MaterialValue *Clone () const = 0;
};

template <class T>
class MaterialConstantValue : public MaterialValue
{
	T Value;
public:
	MaterialConstantValue(const T &value)
		: Value (value) {}

	unsigned int GetType () const { return typeid (T).hash_code (); }
	std::string GetVariableDeclaration (const MaterialTemplate &matemplate) const 
	{ 
		std::stringstream ss;
		ss << "uniform " << matemplate.GetSlot (ValueIndex).Type().ToGLSLTypeString()<< " " << matemplate.GetSlot (ValueIndex).Name() << ";" << std::endl;
		return ss.str(); 
	}

	std::string GetTypeName () const { return "Constant"; }

	void PassToShader (Graphics::Shader &shader, const MaterialTemplate &matemplate) const
	{
		shader[matemplate.GetSlot(ValueIndex).Name()] = Value; //Change to use uniform locations.
	}

	void PassToUniformMap (Graphics::UniformMap &map, const MaterialTemplate &matemplate) const
	{
		map[matemplate.GetSlot(ValueIndex).Name()].Ref(Value);
	}

	MaterialValue *Clone () const
	{
		return new MaterialConstantValue<T> (*this);
	}

};

template <class T>
class MaterialConstantReference : public MaterialValue
{
	const T &Value;
public:
	MaterialConstantReference(const T &value)
		: Value (value) {}

	unsigned int GetType () const { return typeid (T).hash_code (); }
	std::string GetVariableDeclaration (const MaterialTemplate &matemplate) const 
	{ 
		std::stringstream ss;
		ss << "uniform " << matemplate.GetSlot (ValueIndex).Type().ToGLSLTypeString()<< " " << matemplate.GetSlot (ValueIndex).Name() << ";" << std::endl;
		return ss.str(); 
	}

	std::string GetTypeName () const { return "Constant"; }

	void PassToShader (Graphics::Shader &shader, const MaterialTemplate &matemplate) const
	{
		shader[matemplate.GetSlot(ValueIndex).Name()] = Value; //Change to use uniform locations.
	}

	void PassToUniformMap (Graphics::UniformMap &map, const MaterialTemplate &matemplate) const
	{
		map[matemplate.GetSlot(ValueIndex).Name()].Ref(Value);
	}

	MaterialValue *Clone () const
	{
		return new MaterialConstantReference<T> (*this);
	}
};


class MaterialMap : public MaterialValue
{
	Asset<Graphics::Texture2D> Texture;
public:
	MaterialMap (const Asset<Graphics::Texture2D> &tex)
		: Texture(tex) {}

	unsigned int GetResourceHash () const;
	unsigned int GetType () const { return typeid (MaterialMap).hash_code (); }

	std::string GetVariableDeclaration (const MaterialTemplate &matemplate) const;
	std::string GetExtraDefinitions (const MaterialTemplate &matemplate) const;
	std::string GetInitialization (const MaterialTemplate &matemplate) const;

	std::string GetTypeName () const { return "Map"; }

	void PassToShader (Graphics::Shader &shader, const MaterialTemplate &matemplate) const;
	void PassToUniformMap (Graphics::UniformMap &map, const MaterialTemplate &matemplate) const;

	MaterialValue *Clone () const
	{
		return new MaterialMap (*this);
	}
};

class MaterialMapSwizzle : public MaterialValue
{
	Asset<Graphics::Texture2D> Texture;
	std::string Swizzle;
public:
	MaterialMapSwizzle (const Asset<Graphics::Texture2D> &tex, const std::string &swizzle)
		: Texture(tex), Swizzle(swizzle) {}

	unsigned int GetResourceHash () const;
	unsigned int GetType () const;

	std::string GetTypeName () const { return "MapSwizzle"; }

	std::string GetVariableDeclaration (const MaterialTemplate &matemplate) const;
	std::string GetExtraDefinitions (const MaterialTemplate &matemplate) const;
	std::string GetInitialization (const MaterialTemplate &matemplate) const;

	void PassToShader (Graphics::Shader &shader, const MaterialTemplate &matemplate) const;
	void PassToUniformMap (Graphics::UniformMap &map, const MaterialTemplate &matemplate) const;

	MaterialValue *Clone () const
	{
		return new MaterialMapSwizzle (*this);
	}
};

class MaterialFunction : public MaterialValue
{
	std::string Function;
public:
	MaterialFunction (const std::string &function)
		: Function (function) {}

	unsigned int GetResourceHash () const;
	unsigned int GetType () const;
	std::string GetVariableDeclaration (const MaterialTemplate &matemplate) const;
	std::string GetExtraDefinitions (const MaterialTemplate &matemplate) const;
	std::string GetInitialization (const MaterialTemplate &matemplate) const;

	std::string GetTypeName () const { return "Function"; }

	void PassToShader (Graphics::Shader &shader, const MaterialTemplate &matemplate) const {}
	void PassToUniformMap (Graphics::UniformMap &map, const MaterialTemplate &matemplate) const {}

	MaterialValue *Clone () const
	{
		return new MaterialFunction (*this);
	}
};


class MaterialValueSet
{
	Asset<MaterialTemplate> Template;
public:
	class MaterialValueHolder
	{
	public:
		MaterialValueHolder () {}

		std::unique_ptr<MaterialValue> MatValue;
		//That's what I thought mother fucker, no errors here.
		MaterialValueHolder (const MaterialValueHolder &copyme)
			: MatValue (copyme.MatValue != nullptr ? copyme.MatValue->Clone() : nullptr)
		{}

		MaterialValueHolder &operator= (const MaterialValueHolder &copyme)
		{
			MatValue = std::unique_ptr<MaterialValue>(copyme.MatValue->Clone());
			return *this;
		}

		MaterialValueHolder (MaterialValueHolder &&moveme)
			: MatValue (std::move(moveme.MatValue))
		{}

		MaterialValueHolder &operator= (MaterialValueHolder &&moveme)
		{ MatValue = std::move(moveme.MatValue); return *this; }
		

		template<class T>
		void Value (const T &value)
		{
			MatValue.reset(new MaterialConstantValue <T> (value));
		}

		template<class T>
		void Reference (const T& value)
		{
			MatValue.reset(new MaterialConstantReference <T> (value));
		}

		void Map (const Asset<Graphics::Texture2D> &tex)
		{
			MatValue.reset(new MaterialMap (tex));
		}

		void MapSwizzle (const Asset<Graphics::Texture2D> &tex, const std::string &swizzle)
		{
			MatValue.reset(new MaterialMapSwizzle (tex,swizzle));
		}

		void Function (const std::string &function)
		{
			MatValue.reset(new MaterialFunction (function));
		}



	};
public:
	std::vector<MaterialValueHolder> Values;
	explicit MaterialValueSet (const Asset<MaterialTemplate> &matemplate);

	unsigned int GetHash () const;

	MaterialValueHolder &operator [](const std::string &valname);
	const MaterialValueHolder &operator [](const std::string &valname) const;

	void PassToShader (Graphics::Shader &shader) const;
	void PassToUniformMap (Graphics::UniformMap &map) const;
};


}}