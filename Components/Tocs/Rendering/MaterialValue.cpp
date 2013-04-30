#include <algorithm>
#include <Tocs/Core/Hashing.h>

#include "MaterialValue.h"

namespace Tocs {
namespace Rendering {


static unsigned int HashInValue (unsigned int hash, unsigned int value)
{
	return value + (hash << 6) + (hash << 16) - hash;
}

//Material Function

unsigned int MaterialFunction::GetResourceHash () const
{
	return Hashing::Hash (Function);
}

unsigned int MaterialFunction::GetType () const
{
	return HashInValue (typeid (MaterialFunction).hash_code (), GetResourceHash ());
}

std::string MaterialFunction::GetVariableDeclaration (const MaterialTemplate &matemplate) const 
{ 
	std::stringstream ss;
	ss << matemplate.GetSlot (ValueIndex).Type().ToGLSLTypeString()<< " " << matemplate.GetSlot (ValueIndex).Name() << ";" << std::endl;
	return ss.str();
}

std::string MaterialFunction::GetExtraDefinitions (const MaterialTemplate &matemplate) const
{
	std::stringstream ss;
	ss << "void MatFunction" << ValueIndex << " ()" << std::endl << "{" << std::endl << Function << std::endl << "}" << std::endl;
	return ss.str ();
}

std::string MaterialFunction::GetInitialization (const MaterialTemplate &matemplate) const
{
	std::stringstream ss;
	ss << "MatFunction" << ValueIndex << " ();" << std::endl;
	return ss.str();
}

//Material Map

unsigned int MaterialMap::GetResourceHash () const
{
	return Texture.Get().GetID ();
}

std::string MaterialMap::GetVariableDeclaration (const MaterialTemplate &matemplate) const
{
	if (ValueIndex == ResourceIndex) //Then this is the first use of the resource, so we define a sampler.
	{
		std::stringstream ss;
		ss << "uniform sampler2D Texture" << ValueIndex << ";" << std::endl;
		return ss.str();
	}
	return "";
}

std::string MaterialMap::GetExtraDefinitions (const MaterialTemplate &matemplate) const
{
	std::stringstream ss;
	ss << matemplate.GetSlot (ValueIndex).Type().ToGLSLTypeString()<< " " << matemplate.GetSlot (ValueIndex).Name() << ";" << std::endl;
	return ss.str();
}

std::string MaterialMap::GetInitialization (const MaterialTemplate &matemplate) const
{
	std::stringstream ss;
	if (ValueIndex == ResourceIndex) //This is the first use of the resource, sample the texture
	{
		ss << "vec4 Sample" << ResourceIndex << " = texture2D(Texture" << ResourceIndex << ", TextureCoordinate);" << std::endl;
	}
	ss << matemplate.GetSlot(ValueIndex).Name () << " = Sample" << ResourceIndex << "." << Graphics::ShaderVariableType::GetTruncationSwizzle (Graphics::ShaderVariableType::Vector4,matemplate.GetSlot(ValueIndex).Type()) << ";";
	return ss.str();
}

void MaterialMap::PassToShader (Graphics::Shader &shader, const MaterialTemplate &matemplate) const
{
	if (ValueIndex == ResourceIndex)	
	{
		std::stringstream texname;
		texname << "Texture" << ResourceIndex;
		shader[texname.str()] = Texture.Get();
	}
}
void MaterialMap::PassToUniformMap (Graphics::UniformMap &map, const MaterialTemplate &matemplate) const
{
	if (ValueIndex == ResourceIndex)	
	{
		std::stringstream texname;
		texname << "Texture" << ResourceIndex;
		map[texname.str()].Ref(Texture.Get());
	}
}

//Material Swizzle

unsigned int MaterialMapSwizzle::GetResourceHash () const
{
	return Texture.Get().GetID ();
}

unsigned int MaterialMapSwizzle::GetType () const 
{ 
	unsigned int hash = 0;
	hash = HashInValue (hash,typeid (MaterialMapSwizzle).hash_code ());
	for (auto i = Swizzle.begin (); i != Swizzle.end (); ++i)
	{
		hash = HashInValue (hash, *i);
	}
	return hash;
}

std::string MaterialMapSwizzle::GetVariableDeclaration (const MaterialTemplate &matemplate) const
{
	if (ValueIndex == ResourceIndex) //Then this is the first use of the resource, so we define a sampler.
	{
		std::stringstream ss;
		ss << "uniform sampler2D Texture" << ValueIndex << ";" << std::endl;
		return ss.str();
	}
	return "";
}

std::string MaterialMapSwizzle::GetExtraDefinitions (const MaterialTemplate &matemplate) const
{
	std::stringstream ss;
	ss << matemplate.GetSlot (ValueIndex).Type().ToGLSLTypeString()<< " " << matemplate.GetSlot (ValueIndex).Name() << ";" << std::endl;
	return ss.str();
}

std::string MaterialMapSwizzle::GetInitialization (const MaterialTemplate &matemplate) const
{
	std::stringstream ss;
	if (ValueIndex == ResourceIndex) //This is the first use of the resource, sample the texture
	{
		ss << "vec4 Sample" << ResourceIndex << " = texture2D(Texture" << ResourceIndex << ", TextureCoordinate);" << std::endl;
	}
	ss << matemplate.GetSlot(ValueIndex).Name () << " = Sample" << ResourceIndex << "." << Swizzle << ";";
	return ss.str();
}

void MaterialMapSwizzle::PassToShader (Graphics::Shader &shader, const MaterialTemplate &matemplate) const
{
	if (ValueIndex == ResourceIndex)	
	{
		std::stringstream texname;
		texname << "Texture" << ResourceIndex;
		shader[texname.str()] = Texture.Get();
	}
}
void MaterialMapSwizzle::PassToUniformMap (Graphics::UniformMap &map, const MaterialTemplate &matemplate) const
{
	if (ValueIndex == ResourceIndex)	
	{
		std::stringstream texname;
		texname << "Texture" << ResourceIndex;
		map[texname.str()].Ref(Texture.Get());
	}
}

MaterialValueSet::MaterialValueSet(const Asset<MaterialTemplate> &matemplate)
	: Template(matemplate)
{
	Values.resize (Template.Get().SlotCount());
}


unsigned int MaterialValueSet::GetHash () const
{
	unsigned int hash = 0;

	std::vector<unsigned int> resources;

	for (auto i = Values.begin (); i != Values.end (); ++i)
	{
		unsigned int resource = 0;
		if ((*i).MatValue != nullptr)
			resource = (*i).MatValue.get()->GetResourceHash ();
		resources.push_back (resource);
		unsigned int resindex = 0;
		if (resource != 0)
		{
			auto loc = std::find (resources.begin (), resources.end(),resource);
			resindex = loc - resources.begin ();
		}

		if ((*i).MatValue != nullptr)
		{
			(*i).MatValue.get()->ResourceIndex = resindex;
			(*i).MatValue.get()->ValueIndex = resources.size () - 1;
		}

		hash = HashInValue (hash, i - Values.begin());
		hash = HashInValue (hash, resindex);
		if ((*i).MatValue != nullptr)
			hash = HashInValue (hash, (*i).MatValue.get()->GetType ());
	}
	return hash;
}

MaterialValueSet::MaterialValueHolder &MaterialValueSet::operator [](const std::string &valname)
{
	for (int i = 0; i < Template.Get().SlotCount (); ++i)
	{
		if (Template.Get().GetSlot(i).Name() == valname)
			return Values[i];
	}
	throw "This shit isn't here. What are you thinking.";
}
const MaterialValueSet::MaterialValueHolder &MaterialValueSet::operator [](const std::string &valname) const
{
	for (int i = 0; i < Template.Get().SlotCount (); ++i)
	{
		if (Template.Get().GetSlot(i).Name() == valname)
			return Values[i];
	}
	throw "This shit isn't here. What are you thinking.";
}

void MaterialValueSet::PassToShader (Graphics::Shader &shader) const
{
	for (auto i = Values.begin(); i != Values.end (); ++i)
	{
		if ((*i).MatValue != nullptr)
			(*i).MatValue->PassToShader (shader, Template.Get());
	}
}

void MaterialValueSet::PassToUniformMap (Graphics::UniformMap &map) const
{
	for (auto i = Values.begin(); i != Values.end (); ++i)
	{
		if ((*i).MatValue != nullptr)
				(*i).MatValue->PassToUniformMap (map, Template.Get());
	}
}

}}
