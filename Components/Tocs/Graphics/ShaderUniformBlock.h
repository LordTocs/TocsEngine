#pragma once
#include "ShaderTypes.h"

namespace Tocs {
namespace Graphics {

class UBO;
class Shader;

class ShaderUniformBlock
{
	Shader &OwningShader;
	unsigned int BlockIndex;
	unsigned int BufferBindingIndex;
public:
	ShaderUniformBlock(Shader &shader, unsigned int index);


	unsigned int SizeInBytes () const;

	ShaderUniformBlock &operator= (UBO &ubo);


	bool UsedInShader (ShaderType type) const;
};

}}