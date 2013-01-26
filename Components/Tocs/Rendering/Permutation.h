#pragma once
#include <Tocs/Graphics/Shader.h>
#include "PermutationValueSet.h"
#include "PermutationID.h"

namespace Tocs {
namespace Rendering {

class Permutation
{
	Permutations::PermutationID ID;
	Graphics::ShaderCode ConstructedShader;
	Permutation(const Permutation &);
public:
	Permutation(const Permutations::PermutationID &id, Graphics::ShaderCode pixel);
	Permutation(Permutation &&moveme);
	
	Graphics::ShaderCode &GetCode () { return ConstructedShader; }

	void Apply (const Permutations::PermutationValueSet &values, Graphics::Shader &shader);
};

}}