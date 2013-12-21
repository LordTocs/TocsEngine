#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/Texture.h>
#include <Tocs/Graphics/ShaderInput.h>
#include <Tocs/Core/Hashing.h>
#include <Tocs/Core/Tokenizer.h>
#include "ShaderPermutationTemplate.h"
#include <sstream>
#include <type_traits>
#include <memory>


namespace Tocs {
namespace Rendering {

class ShaderPermutationInput
{
public:
	class ValueSlot;
private:
	class Value
	{
	public:
		virtual ~Value() {}

		virtual unsigned int GetTypeHash() const = 0;
		virtual unsigned int GetResourceID() const { return 0; };
		virtual std::string GetTypeName() const = 0;

		virtual void Apply(Graphics::ShaderInput &input,const  ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const = 0;
		virtual void Apply(Graphics::UniformMap &input,const  ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const = 0;
		virtual std::string GetVariableDeclaration(const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const = 0;
		virtual std::string GetInitialization(const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const { return ""; }
		virtual std::string GetExtraDefinitions(const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const { return ""; }

	};
public:
	class ValueSlot
	{
	public:
		ValueSlot(const ValueSlot &) = delete;
		ValueSlot &operator= (const ValueSlot &) = delete;
		unsigned int ResourceIndex;
		unsigned int ValueIndex;
		std::unique_ptr<Value> Slot;
		std::string Name;

		ValueSlot(ValueSlot &&moveme)
			: ResourceIndex(moveme.ResourceIndex),
			ValueIndex(moveme.ValueIndex),
			Slot(std::move(moveme.Slot)),
			Name(std::move(moveme.Name)) {}

		ValueSlot &operator= (ValueSlot &&moveme)
		{
			ResourceIndex = moveme.ResourceIndex;
			ValueIndex = moveme.ValueIndex;
			Slot = std::move(moveme.Slot);
			Name = std::move(moveme.Name);
			return *this;
		}

		bool operator< (const ValueSlot &op2)
		{
			return Name < op2.Name;
		}

		ValueSlot(const std::string &name)
			: Name(name) {}

		void ParseValue(Lexing::Tokenizer &tokens);

		template <class T>
		void Value(const T &value);

		void Texture(const Asset<Graphics::Texture2D> &texture);
		void Swizzle(const Asset<Graphics::Texture2D> &texture, const std::string &swizzle);
	};
private:
	template<class T>
	class ConstantValue : public Value
	{
	public:
		T Constant;

		ConstantValue(const T &value)
			: Constant(value) {}

		unsigned int GetTypeHash() const
		{
			return typeid(T).hash_code();
		}

		void Apply(Graphics::ShaderInput &input,const  ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const
		{
			const PermutationParameter &param = *(temp.Begin() + index);
			input[param.Name].Ref(Constant); //Is Ref Safe?
		}

		void Apply(Graphics::UniformMap &input,const  ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const
		{
			const PermutationParameter &param = *(temp.Begin() + index);
			input[param.Name].Ref(Constant); //Is Ref Safe?
		}

		std::string GetVariableDeclaration(const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const
		{
			const PermutationParameter &param = *(temp.Begin() + index);
			std::stringstream ss;
			ss << "uniform " << param.Type.ToGLSLTypeString() << " " << param.Name << ";";
			return ss.str();
		}

		std::string GetTypeName() const
		{
			return "Constant";
		}
	};

private:

	class TextureValue : public Value
	{
	public:
		Asset<Graphics::Texture2D> Texture;

		TextureValue(const Asset<Graphics::Texture2D> &texture)
			: Texture(texture) {}

		unsigned int GetTypeHash() const
		{
			return typeid(TextureValue).hash_code();
		}

		unsigned int GetResourceID() const { return Texture.Get().GetID(); }

		void Apply(Graphics::ShaderInput &input,const  ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const;
		void Apply(Graphics::UniformMap &input,const  ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const;

		std::string GetVariableDeclaration(const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const;
		std::string GetInitialization(const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const;
		std::string GetExtraDefinitions(const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const;

		std::string GetTypeName() const
		{
			return "Texture";
		}
	};

	class TextureSwizzleValue : public Value
	{
	public:
		Asset<Graphics::Texture2D> Texture;
		std::string Swizzle;

		TextureSwizzleValue(const Asset<Graphics::Texture2D> &texture, const std::string &swizzle)
			: Texture(texture), Swizzle(swizzle) {}

		unsigned int GetTypeHash() const
		{
			return Hashing::HashInValue(typeid(TextureSwizzleValue).hash_code(), Hashing::Hash(Swizzle));
		}

		unsigned int GetResourceID() const { return Texture.Get().GetID(); }

		void Apply(Graphics::ShaderInput &input, const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const;
		void Apply(Graphics::UniformMap &input, const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const;

		std::string GetVariableDeclaration(const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const;
		std::string GetInitialization(const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const;
		std::string GetExtraDefinitions(const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const;

		std::string GetTypeName() const
		{
			return "Texture";
		}
	};
public:
	std::vector<ValueSlot> Values;
	ShaderPermutationInput() {}
	ShaderPermutationInput(const ShaderPermutationInput &) = delete;
	ShaderPermutationInput &operator= (const ShaderPermutationInput &) = delete;

	ShaderPermutationInput(ShaderPermutationInput &&moveme)
		: Values(std::move(moveme.Values)) {}

	ShaderPermutationInput &operator= (ShaderPermutationInput &&moveme)
	{ Values = std::move(moveme.Values); }

	ValueSlot &operator [](const std::string &valname);
	const ValueSlot &operator [](const std::string &valname) const;

	unsigned int GetHash() const;

	void Apply(Graphics::ShaderInput &input, const ShaderPermutationTemplate &temp) const;
	void Apply(Graphics::UniformMap &input, const ShaderPermutationTemplate &temp) const;
};

template <class T>
void ShaderPermutationInput::ValueSlot::Value(const T &value)
{
	ConstantValue<T> *constslot = dynamic_cast<ConstantValue<T>*>(Slot.get());
	if (constslot != nullptr)
	{
		constslot->Constant = value;
	}
	else
	{
		Slot.reset(new ConstantValue<T>(value));
	}
}

}}