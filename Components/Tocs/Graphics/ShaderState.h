#pragma once
#include <functional>
#include <memory>
#include "ShaderUniform.h"
#include "Shader.h"
namespace Tocs {
namespace Graphics {

class ShaderStateUsage
{
public:
	int UsageCount;
	int CommonIndex;
	int LastBindIndex;

	ShaderStateUsage()
		: UsageCount(0)
		, CommonIndex(-1)
		, LastBindIndex(-1)
	{}
};

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
			container->~ShaderStateContainer();
		}
		static void Mover(void *From, void *To)
		{
			ShaderStateContainer<T> *from = reinterpret_cast<ShaderStateContainer<T>*>(From);
			new (To)ShaderStateContainer(std::move(*from));
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
			container->~ShaderStateContainer();//Deconstruct because of inplace new.
		}
		static void Mover(void *From, void *To)
		{
			ShaderStateContainer<const T &> *from = reinterpret_cast<ShaderStateContainer<const T &>*>(From);
			new (To)ShaderStateContainer(std::move(*from));
		}
	};
public:
	class ShaderStateValue
	{
		unsigned char StateBuffer[sizeof(ShaderStateContainer<Math::Matrix4>)];
		std::string Name_;
		void(*BindFunc)(const void*, ShaderUniform&);
		void(*DeleteFunc)(void*);
		void(*MoveFunc)(void*, void*);

	public:
		ShaderStateValue(const std::string &name)
			: Name_(name)
			, BindFunc(nullptr)
			, DeleteFunc(nullptr)
			, MoveFunc(nullptr)
		{}

		ShaderStateValue(ShaderStateValue &&moveme)
			: Name_(std::move(moveme.Name_))
			, BindFunc(moveme.BindFunc)
			, DeleteFunc(moveme.DeleteFunc)
			, MoveFunc(moveme.MoveFunc)
		{
			if (moveme.HasState())
			{
				MoveFunc(moveme.StateBuffer, StateBuffer);
				moveme.BindFunc = nullptr;
				moveme.DeleteFunc = nullptr;
				moveme.MoveFunc = nullptr;
			}
		}
		ShaderStateValue(const ShaderStateValue &copyme) = delete;

		~ShaderStateValue() { Clear(); } 
		//ShaderStateValue(ShaderStateValue &&moveme);
		ShaderStateValue &operator= (const ShaderStateValue &copyme) = delete;
		ShaderStateValue &operator= (ShaderStateValue &&moveme)
		{
			Clear();

			Name_ = std::move(moveme.Name_);
			BindFunc = moveme.BindFunc;
			DeleteFunc = moveme.DeleteFunc;
			MoveFunc = moveme.MoveFunc;
			if (moveme.HasState())
			{
				MoveFunc(moveme.StateBuffer, StateBuffer);
				moveme.BindFunc = nullptr;
				moveme.DeleteFunc = nullptr;
				moveme.MoveFunc = nullptr;
			}
			return *this;
		}

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
			MoveFunc = ShaderStateContainer<T>::Mover;
		}

		template <class T>
		void Ref(const T &ref)
		{
			static_assert(sizeof (ShaderStateContainer<const T &>) <= sizeof(StateBuffer), "ShaderStateContainer of type is too large to fit into buffer");
			Clear();
			new (StateBuffer)ShaderStateContainer<const T &>(ref);
			DeleteFunc = ShaderStateContainer<const T &>::Deleter;
			BindFunc = ShaderStateContainer<const T &>::DoBind;
			MoveFunc = ShaderStateContainer<const T &>::Mover;
		}
	};
private:
	std::vector<ShaderStateValue> Values;
	ShaderStateUsage Usages[5];
public:
	ShaderState() {}
	ShaderState(const ShaderState &) = delete;
	ShaderState(ShaderState &&moveme)
		: Values(std::move(moveme.Values)) {}

	ShaderState &operator=(const ShaderState &) = delete;


	bool HasValue(const std::string &uniformname) const;
	unsigned int ValueCount() const { return Values.size(); }

	ShaderStateValue &operator[] (const std::string &uniformname);
	const ShaderStateValue &operator[] (const std::string &uniformname) const;

	ShaderStateValue &operator[] (unsigned int index) { return Values[index]; }
	const ShaderStateValue &operator[] (unsigned int index) const { return Values[index]; }

	ShaderStateValue &AddValue(const std::string &name);

	ShaderStateUsage &GetUsage(int index) { return Usages[index]; }
	const ShaderStateUsage &GetUsage(int index) const { return Usages[index]; }
};

class ShaderStateMapping
{
	Shader *MappedShader;
	const ShaderState *State;
	std::vector<ShaderUniform> Uniforms;
public:
	ShaderStateMapping(Shader &shader, const ShaderState &state);

	void Bind();

	const ShaderState &GetState() const { return *State; }
};

class ShaderStateSet
{
	Shader *MappedShader;
	std::vector<ShaderStateMapping> Mappings;
public:
	ShaderStateSet(Shader &shader)
		: MappedShader(&shader) {}

	ShaderStateSet(const ShaderStateSet &) = delete;
	ShaderStateSet(ShaderStateSet &&moveme)
		: MappedShader(moveme.MappedShader), Mappings(std::move(moveme.Mappings)) {}

	Shader &GetShader() { return *MappedShader; }
	const Shader &GetShader() const { return *MappedShader; }

	void MapState(const ShaderState &state);

	int MappingCount() const { return Mappings.size(); }

	ShaderStateMapping &GetMapping(int index) { return Mappings[index]; }
	const ShaderStateMapping &GetMapping(int index) const { return Mappings[index]; }

	void BindAll();

	auto begin() -> decltype(Mappings.begin()) { return Mappings.begin(); }
	auto end  () -> decltype(Mappings.end()) { return Mappings.end(); }
};


}}