#include "ShaderPool.h"
#include <Tocs/Core/Hashing.h>
#include <iostream>
namespace Tocs {
namespace Rendering {

ShaderPool ShaderPool::Global;

Graphics::Shader *ShaderPool::LookUp (unsigned int hash)
{
	auto s = Shaders.find(hash);
	if (s != Shaders.end ())
	{
		return &(*s).second;
	}
	return nullptr;
}

Graphics::Shader &ShaderPool::Emplace (unsigned int hash, Graphics::Shader &&shader)
{
	return Shaders.insert (std::make_pair(hash,std::move(shader))).first->second;
}

static unsigned int HashInValue (unsigned int hash, unsigned int value)
{
        return value + (hash << 6) + (hash << 16) - hash;
}

void ShaderConstruction::AddCode (const Graphics::ShaderCode &code)
{
	InputCode.push_back(&code);
	IDHash = HashInValue (IDHash,code.GetID());
}

Graphics::Shader &ShaderConstruction::Link (ShaderPool &pool) const
{
	Graphics::Shader *result = pool.LookUp (IDHash);
	if (result != nullptr)
	{
		return *result;
	}


	Graphics::Shader builtresult;

	for (auto i = InputCode.begin (); i != InputCode.end (); ++i)
	{
		builtresult.AddCode(**i);
	}

	builtresult.Link ();

	if (!builtresult.Linked())
	{
		std::cout << 
		"Shader Construction Failed" << std::endl <<
		"-========================-" << std::endl <<
		builtresult.GetLinkErrors () << std::endl;
	}


	return pool.Emplace(IDHash,std::move(builtresult));
}

}}