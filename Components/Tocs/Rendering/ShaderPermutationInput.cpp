#include "ShaderPermutationInput.h"
#include <algorithm>
#include <cassert>
#include <Tocs/Core/Float.h>
#include <Tocs/Core/Integer.h>


using namespace Tocs::Lexing;

namespace Tocs {
namespace Rendering {


void ShaderPermutationInput::ValueSlot::Texture(const Asset<Graphics::Texture2D> &texture)
{
	ShaderPermutationInput::TextureValue *slot = dynamic_cast<ShaderPermutationInput::TextureValue*>(Slot.get());
	if (slot != nullptr)
	{
		slot->Texture = texture;
	}
	else
	{
		Slot.reset(new ShaderPermutationInput::TextureValue(texture)); //Invalidate
	}
}

void ShaderPermutationInput::ValueSlot::Swizzle(const Asset<Graphics::Texture2D> &texture, const std::string &swizzle)
{
	ShaderPermutationInput::TextureSwizzleValue *slot = dynamic_cast<ShaderPermutationInput::TextureSwizzleValue*>(Slot.get());
	if (slot != nullptr)
	{
		slot->Texture = texture;
		slot->Swizzle = swizzle; //Swizzles can invalidate the generated shader...
	}
	else
	{
		Slot.reset(new ShaderPermutationInput::TextureSwizzleValue(texture,swizzle)); //Invalidate
	}
}

void ShaderPermutationInput::ValueSlot::VertexInput(const std::string &name)
{
	ShaderPermutationInput::VertexInputValue *slot = dynamic_cast<ShaderPermutationInput::VertexInputValue*>(Slot.get());
	if (slot != nullptr)
	{
		slot->Name = name; //Swizzles can invalidate the generated shader...
	}
	else
	{
		Slot.reset(new ShaderPermutationInput::VertexInputValue(name)); //Invalidate
	}
}

void ShaderPermutationInput::ValueSlot::ParseValue(Tokenizer &tokens)
{
	auto valuedata = tokens.GetTokenData();

	if (valuedata == TokenType::Float)
	{
		Value(Float::Parse(valuedata.GetToken()));
	}
	else if (valuedata == TokenType::Integer)
	{
		Value(Integer::Parse32(valuedata.GetToken()));
	}
	else if (valuedata == "tex")
	{
		if (!tokens.Is("("))
		{
		}

		TokenData filetoken = tokens.GetTokenData();
		if (filetoken.GetType() != TokenType::StringLiteral)
		{
		}

		std::string filename = filetoken.GetToken().substr(1, filetoken.GetToken().size() - 2);

		if (!tokens.Is(")"))
		{
		}

		if (!tokens.Is("."))
		{
			Texture(Asset<Graphics::Texture2D>::Load(filename));
			return;
		}

		auto swizzle = tokens.GetTokenData();

		if (swizzle.GetType() != TokenType::Word)
		{ //OH GOD PANIC
		}

		Swizzle(Asset<Graphics::Texture2D>::Load(filename), swizzle.GetToken());
	}
	else if (valuedata == "color")
	{
		if (!tokens.Is("("))
		{
		}

		int r = Integer::Parse32(tokens.GetToken());

		if (!tokens.Is(","))
		{}

		int g = Integer::Parse32(tokens.GetToken());

		if (!tokens.Is(","))
		{
		}

		int b = Integer::Parse32(tokens.GetToken());

		int a = 255;
		
		if (tokens.Is(","))
		{
			a = Integer::Parse32(tokens.GetToken());
		}

		Value(Math::Color(r, g, b, a));

		if (!tokens.Is(")"))
		{
		}
	}
	else if (valuedata == "<")
	{
		float v0 = Float::Parse(tokens.GetToken());
		if (!tokens.Is(","))
		{
		}
		float v1 = Float::Parse(tokens.GetToken());
		if (!tokens.Is(","))
		{
			if (tokens.Is(">"))
			{
				Value(Math::Vector2(v0, v1));
				return;
			}
		}
		float v2 = Float::Parse(tokens.GetToken());
		if (!tokens.Is(","))
		{
			if (tokens.Is(">"))
			{
				Value(Math::Vector3(v0, v1, v2));
				return;
			}
		}
		float v3 = Float::Parse(tokens.GetToken());
		if (!tokens.Is(">"))
		{
		}
		Value(Math::Vector4(v0, v1, v2, v3));
	}
	else if (valuedata == "#")
	{
		auto colortoken = tokens.GetToken();
		Value(Math::Color::FromHex(std::string("#") + colortoken));
	}
	else if (valuedata == "vertex_input")
	{
		if (!tokens.Is("("))
		{
		}

		TokenData nametoken = tokens.GetTokenData();
		if (nametoken.GetType() != TokenType::StringLiteral)
		{
		}

		std::string name = nametoken.GetToken().substr(1, nametoken.GetToken().size() - 2);

		if (!tokens.Is(")"))
		{
		}

		VertexInput(name);
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void ShaderPermutationInput::TextureValue::Apply(Graphics::ShaderInput &input,const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const
{
	const PermutationParameter &param = *(temp.Begin() + index);
	std::stringstream ss;
	ss << "Texture_" << slot.ResourceIndex;
	input[ss.str()].Ref(Texture);
}

void ShaderPermutationInput::TextureValue::Apply(Graphics::UniformMap &input,const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const
{
	const PermutationParameter &param = *(temp.Begin() + index);
	std::stringstream ss;
	ss << "Texture_" << slot.ResourceIndex;
	input[ss.str()].Ref(Texture);
}


std::string ShaderPermutationInput::TextureValue::GetVariableDeclaration(const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const
{
	const PermutationParameter &param = *(temp.Begin() + index);
	if (slot.ValueIndex == slot.ResourceIndex)
	{
		std::stringstream ss;
		ss << "uniform sampler2D Texture_" << slot.ResourceIndex << ";";
		return ss.str();
	}

	return std::string();
}

std::string ShaderPermutationInput::TextureValue::GetInitialization(const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const
{
	std::stringstream ss;
	if (slot.ValueIndex == slot.ResourceIndex) //This is the first use of the resource, sample the texture
	{
		ss << "vec4 Sample" << slot.ResourceIndex << " = texture2D(Texture_" << slot.ResourceIndex << ", TextureCoordinate);" << std::endl;
	}
	const PermutationParameter &param = *(temp.Begin() + index);
	ss << param.Name << " = Sample" << slot.ResourceIndex << "." << Graphics::ShaderVariableType::GetTruncationSwizzle(Graphics::ShaderVariableType::Vector4, param.Type) << ";";
	return ss.str();
}
std::string ShaderPermutationInput::TextureValue::GetExtraDefinitions(const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const
{
	std::stringstream ss;
	const PermutationParameter &param = *(temp.Begin() + index);
	ss << param.Type.ToGLSLTypeString() << " " << param.Name << ";" << std::endl;
	return ss.str();
}

///////////////

void ShaderPermutationInput::TextureSwizzleValue::Apply(Graphics::ShaderInput &input,const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const
{
	const PermutationParameter &param = *(temp.Begin() + index);
	std::stringstream ss;
	ss << "Texture_" << slot.ResourceIndex;
	input[ss.str()].Ref(Texture);
}

void ShaderPermutationInput::TextureSwizzleValue::Apply(Graphics::UniformMap &input,const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const
{
	const PermutationParameter &param = *(temp.Begin() + index);
	std::stringstream ss;
	ss << "Texture_" << slot.ResourceIndex;
	input[ss.str()].Ref(Texture);
}

std::string ShaderPermutationInput::TextureSwizzleValue::GetVariableDeclaration(const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const
{
	const PermutationParameter &param = *(temp.Begin() + index);
	if (slot.ValueIndex == slot.ResourceIndex)
	{
		std::stringstream ss;
		ss << "uniform sampler2D Texture_" << slot.ResourceIndex << ";";
		return ss.str();
	}

	return std::string();
}

std::string ShaderPermutationInput::TextureSwizzleValue::GetInitialization(const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const
{
	std::stringstream ss;
	if (slot.ValueIndex == slot.ResourceIndex) //This is the first use of the resource, sample the texture
	{
		ss << "vec4 Sample" << slot.ResourceIndex << " = texture2D(Texture_" << slot.ResourceIndex << ", TextureCoordinate);" << std::endl;
	}
	const PermutationParameter &param = *(temp.Begin() + index);
	ss << param.Name << " = Sample" << slot.ResourceIndex << "." << Graphics::ShaderVariableType::GetTruncationSwizzle(Graphics::ShaderVariableType::Vector4, param.Type) << ";";
	return ss.str();
}

std::string ShaderPermutationInput::TextureSwizzleValue::GetExtraDefinitions(const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const
{
	std::stringstream ss;
	const PermutationParameter &param = *(temp.Begin() + index);
	ss << param.Type.ToGLSLTypeString() << " " << param.Name << ";" << std::endl;
	return ss.str();
}
//////////////////////////////////////////////////////////////////////////////


void ShaderPermutationInput::VertexInputValue::Apply(Graphics::ShaderInput &input, const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const
{
}

void ShaderPermutationInput::VertexInputValue::Apply(Graphics::UniformMap &input, const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const
{
}

std::string ShaderPermutationInput::VertexInputValue::GetVariableDeclaration(const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const
{
	const PermutationParameter &param = *(temp.Begin() + index);
	std::stringstream ss;
	ss << "in ";
	ss << param.Type.ToGLSLTypeString() << " " << param.Name << ";";
	return ss.str();
}

std::string ShaderPermutationInput::VertexInputValue::GetInitialization(const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const
{
	return std::string();
}

std::string ShaderPermutationInput::VertexInputValue::GetExtraDefinitions(const ShaderPermutationTemplate &temp, unsigned int index, const ValueSlot &slot) const
{
	return std::string();
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


ShaderPermutationInput::ValueSlot &ShaderPermutationInput::operator [](const std::string &valname)
{
	auto i = std::lower_bound(Values.begin(), Values.end(), valname, [](const ValueSlot &slot, const std::string &name) { return slot.Name < name; });
	if (i != Values.end() && i->Name == valname)
	{
		return (*i);
	}
	return *Values.emplace(i, valname);
}

const ShaderPermutationInput::ValueSlot &ShaderPermutationInput::operator [](const std::string &valname) const
{
	auto slot = GetSlot(valname);
	if (slot != nullptr)
		assert(false);
	return *slot;
}

ShaderPermutationInput::ValueSlot *ShaderPermutationInput::GetSlot(const std::string &valname)
{
	auto i = std::lower_bound(Values.begin(), Values.end(), valname, [](const ValueSlot &slot, const std::string &name) { return slot.Name < name; });
	if (i == Values.end())
		return static_cast<ValueSlot *>(nullptr);
	if (i->Name == valname)
	{
		return &(*i);
	}
	return static_cast<ValueSlot *>(nullptr);
}
const ShaderPermutationInput::ValueSlot *ShaderPermutationInput::GetSlot(const std::string &valname) const
{
	auto i = std::lower_bound(Values.begin(), Values.end(), valname, [](const ValueSlot &slot, const std::string &name) { return slot.Name < name; });
	if (i == Values.end())
		return static_cast<ValueSlot *>(nullptr);
	if (i->Name == valname)
	{
		return &(*i);
	}
	return static_cast<ValueSlot *>(nullptr);
}

void ShaderPermutationInput::Apply(Graphics::ShaderInput &input,const ShaderPermutationTemplate &temp) const
{
	auto p = temp.Begin();
	for (auto i = Values.begin(); i != Values.end(); ++i)
	{
		while (p != temp.End() && p->Name != i->Name && p->Name < i->Name)
		{ ++p; }
		if (p == temp.End())
			break;
		if (p->Name != i->Name)
			continue;

		i->Slot->Apply(input, temp, p - temp.Begin(),*i);
	}
}

void ShaderPermutationInput::Apply(Graphics::UniformMap &input,const ShaderPermutationTemplate &temp) const
{
	auto p = temp.Begin();
	for (auto i = Values.begin(); i != Values.end(); ++i)
	{
		while (p != temp.End() && p->Name != i->Name && p->Name < i->Name)
		{
			++p;
		}
		if (p == temp.End())
			break;
		if (p->Name != i->Name)
			continue;

		i->Slot->Apply(input, temp, p - temp.Begin(), *i);
	}
}

unsigned int ShaderPermutationInput::GetHash() const
{
	unsigned int hash = 0;

	std::vector<unsigned int> resources;

	for (auto i = Values.begin(); i != Values.end(); ++i)
	{
		unsigned int resource = 0;
		if ((*i).Slot != nullptr)
			resource = (*i).Slot.get()->GetResourceID();
		resources.push_back(resource);
		unsigned int resindex = 0;
		if (resource != 0)
		{
			auto loc = std::find(resources.begin(), resources.end(), resource); //finds first instance
			resindex = loc - resources.begin();
			const_cast <unsigned int &> ((*i).ResourceIndex) = resindex;
		}
		const_cast<unsigned int &> ((*i).ValueIndex) = i - Values.begin();
		hash = Hashing::HashInValue(hash, i - Values.begin());
		hash = Hashing::HashInValue(hash, resindex);
		if ((*i).Slot != nullptr)
			hash = Hashing::HashInValue(hash, (*i).Slot.get()->GetTypeHash());
	}
	return hash;
}

}}