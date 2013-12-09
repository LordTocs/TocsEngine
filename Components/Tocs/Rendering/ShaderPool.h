#pragma once
#include <Tocs/Graphics/Shader.h>
#include <map>
#include <vector>
//#include "Shading.h"

namespace Tocs {
namespace Rendering {

class Geometry;

class ShaderPool
{
	std::map<unsigned int, Graphics::Shader> Shaders;

	Graphics::Shader &Emplace(unsigned int hash, Graphics::Shader &&shader);

	Graphics::Shader *LookUp (unsigned int hash);
public:
	friend class ShaderConstruction;
	static ShaderPool Global;
};

class ShaderConstruction
{
	std::vector<const Graphics::ShaderCode *> InputCode;
	unsigned int IDHash;
public:
	void AddCode (const Graphics::ShaderCode &code);

	Graphics::Shader &Link (ShaderPool &pool) const;
};


}}