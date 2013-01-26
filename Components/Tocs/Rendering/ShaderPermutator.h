#pragma once
#include <algorithm>
#include <vector>
#include <map>
#include "PermutationField.h"
#include "PermutationID.h"
#include "Permutation.h"
#include "ShaderTemplate.h"
#include <Tocs/Graphics/Shader.h>

namespace Tocs {
namespace Rendering {

namespace Permutations { class PermutationID; }

class ShaderPermutator
{
	
	std::map<Permutations::PermutationID, Permutation> Permutations;
	ShaderPermutator(const ShaderPermutator &); //NO COPY.
public:
	Permutations::ShaderTemplate Template;
	ShaderPermutator(const std::string &templatefile);
	ShaderPermutator(ShaderPermutator &&moveme);

	friend class Permutations::PermutationID;
	Permutation &GetPermutation (Permutations::PermutationValueSet &values);

	static ShaderPermutator LoadFromFile (const std::string &filename);
};


}}