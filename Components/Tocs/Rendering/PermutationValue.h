#pragma once
#include <vector>
#include "PermutationID.h"
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/Texture.h>
#include <Tocs/Graphics/ShaderUniform.h>

namespace Tocs {
namespace Rendering {
namespace Permutations {

class PermutationValue
{
public:
	virtual ~PermutationValue()
	{}

	virtual const PermutationValueType &GetType () const = 0;
	virtual void FillValueInfo (std::vector<Asset<Graphics::Texture2D>> &textures, PermutationID::ValueInfo &info) = 0;
	virtual void BindToUniform (Graphics::ShaderUniform &uniform) = 0;
	virtual PermutationValue *Clone () const = 0;
};

class TextureValue : public PermutationValue
{
	Asset<Graphics::Texture2D> Texture;
public:
	TextureValue (const Asset<Graphics::Texture2D> &texture)
		: Texture(texture)
	{
	}

	const PermutationValueType &GetType () const
	{
		return PermutationValueType::Map;
	}
	void FillValueInfo (std::vector<Asset<Graphics::Texture2D>> &textures, PermutationID::ValueInfo &info);

	void BindToUniform (Graphics::ShaderUniform &uniform)
	{
		uniform = Texture.Get ();
	}

	PermutationValue *Clone () const
	{
		return new TextureValue (*this);
	}
};

class TextureComponentValue : public PermutationValue
{
	Asset<Graphics::Texture2D> Texture;
	char Component;
public:
	TextureComponentValue (const Asset<Graphics::Texture2D> &texture, char component)
		: Texture(texture), Component(component)
	{
	}

	const PermutationValueType &GetType () const
	{
		return PermutationValueType::MapComponent;
	}
	void FillValueInfo (std::vector<Asset<Graphics::Texture2D>> &textures, PermutationID::ValueInfo &info);
	
	void BindToUniform (Graphics::ShaderUniform &uniform)
	{
		uniform = Texture.Get ();
	}
	PermutationValue *Clone () const
	{
		return new TextureComponentValue (*this);
	}
};

template <class T>
class ConstantValue : public PermutationValue
{
	T Value;
public:
	ConstantValue (const T &value)
		: Value(value)
	{
	}

	const PermutationValueType &GetType () const { return PermutationValueType::Constant; }
	void FillValueInfo (std::vector<Asset<Graphics::Texture2D>> &textures, PermutationID::ValueInfo &info)
	{
		info.Type = PermutationValueType::Constant;
	}

	void BindToUniform (Graphics::ShaderUniform &uniform)
	{
		uniform = Value;
	}

	PermutationValue *Clone () const
	{
		return new ConstantValue<T> (*this);
	}

};

}}}