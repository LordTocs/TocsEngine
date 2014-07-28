#pragma once
#include <functional>
#include <memory>
#include "ShaderUniform.h"
#include "Shader.h"
namespace Tocs {
namespace Graphics {

class ShaderState
{
	template<class T>
	class ShaderStateContainer
	{
		T Value;
	public:
		ShaderStateContainer(const T &value)
			: Value(value) {}

		//Functions for explictly storing, Maybe faster than VTable?
		static void DoBind(const void *Container, ShaderUniform &uniform)
		{
			const ShaderStateContainer<T> *container = reinterpret_cast<const ShaderStateContainer<T>*>(Container);
			uniform = container->Value;
		}
		static void Deleter(void *Container)
		{
			ShaderStateContainer<T> *container = reinterpret_cast<ShaderStateContainer<T>*>(Container);
			delete container;
		}
	};

	template<class T>
	class ShaderStateContainer<const T &>
	{
		const T *Value;
	public:
		ShaderStateContainer(const T &value)
			: Value(&value) {}

		//Functions for explictly storing, Maybe faster than VTable?
		static void DoBind(const void *Container, ShaderUniform &uniform)
		{
			const ShaderStateContainer<const T &> *container = reinterpret_cast<const ShaderStateContainer<const T &>*>(Container);
			uniform = *container->Value;
		}
		static void Deleter(void *Container)
		{
			ShaderStateContainer<const T &> *container = reinterpret_cast<ShaderStateContainer<const T &>*>(Container);
			container.~ShaderStateContainer<const T &>();//Deconstruct because of inplace new.
		}
	};
public:
	class ShaderStateValue
	{
		unsigned char StateBuffer[sizeof(ShaderStateContainer<Math::Matrix4>)];
		std::string Name_;
		void(*BindFunc)(const void*, ShaderUniform&);
		void(*DeleteFunc)(void*);

	public:
		ShaderStateValue(const std::string &name)
			: Name_(name), BindFunc(nullptr) {}

		ShaderStateValue(ShaderStateValue &&moveme);
		ShaderStateValue(const ShaderStateValue &copyme) = delete;

		~ShaderStateValue() { Clear(); }
		//ShaderStateValue(ShaderStateValue &&moveme);
		ShaderStateValue &operator= (const ShaderStateValue &copyme) = delete;
		//ShaderStateValue &operator= (const ShaderStateValue &moveme);

		void Bind(ShaderUniform &uniform) const { BindFunc(StateBuffer, uniform); }
		const std::string &Name() const { return Name_; }

		bool HasState() const { return DeleteFunc != nullptr; }

		void Clear()
		{
			if (DeleteFunc)
				DeleteFunc(StateBuffer);
			DeleteFunc = nullptr;
			BindFunc = nullptr;
		}

		template <class T>
		void Value(const T &value)
		{
			//Check if type fits
			static_assert(sizeof (ShaderStateContainer<T>) <= sizeof(StateBuffer), "ShaderStateContainer of type is too large to fit into buffer");
			Clear();
			new (StateBuffer)ShaderStateContainer<T>(value);
			DeleteFunc = ShaderStateContainer<T>::Deleter;
			BindFunc = ShaderStateContainer<T>::DoBind;
		}

		template <class T>
		void Ref(const T &ref)
		{
			static_assert(sizeof (ShaderStateContainer<const T &>) <= sizeof(StateBuffer), "ShaderStateContainer of type is too large to fit into buffer");
			Clear();
			new (StateBuffer)ShaderStateContainer<const T &>(value);
			DeleteFunc = ShaderStateContainer<const T &>::Deleter;
			BindFunc = ShaderStateContainer<const T &>::DoBind;
		}
	};
private:
	std::vector<ShaderStateValue> Values;
public:
	ShaderState();

	bool HasValue(const std::string &uniformname) const;
	unsigned int ValueCount() const { return Values.size(); }

	ShaderStateValue &operator[] (const std::string &uniformname);
	const ShaderStateValue &operator[] (const std::string &uniformname) const;

	ShaderStateValue &operator[] (unsigned int index) { return Values[index]; }
	const ShaderStateValue &operator[] (unsigned int index) const { return Values[index]; }

	void AddValue(const std::string &name);
};

class ShaderStateMapping
{
	Shader *MappedShader;
	class Mapping
	{
		const ShaderState *State;
		std::vector<ShaderUniform> Uniforms;
	public:
		Mapping(Shader &shader, const ShaderState &state);
		void Bind();
	};
	std::vector<Mapping> Mappings;
public:
	ShaderStateMapping(Shader &mappedshader)
		: MappedShader(&mappedshader) {}

	void MapState(const ShaderState &state)
	{
		Mappings.emplace_back(*MappedShader, state);
	}

};

}}