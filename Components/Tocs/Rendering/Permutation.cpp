#include <iostream>
#include <sstream>
#include "Permutation.h"

using namespace std;
using namespace Tocs::Rendering::Permutations;

namespace Tocs {
namespace Rendering {

Permutation::Permutation(const Permutations::PermutationID &id, Graphics::ShaderCode pixel)
	: ID (id),
	  ConstructedShader(std::move(pixel))
{
}

Permutation::Permutation(Permutation &&moveme)
	: ID(std::move(moveme.ID)),
	  ConstructedShader(std::move(moveme.ConstructedShader))
{
}


void Permutation::Apply (const Permutations::PermutationValueSet &values, Graphics::Shader &shader)
{
	for (auto i = values.begin (); i != values.end (); ++i)
	{
		if (((*i).second.get ()->GetType () == PermutationValueType::Map) ||
			((*i).second.get ()->GetType () == PermutationValueType::MapComponent))
		{
			auto idvalue = ID[i->first];
			if (idvalue.BinderValue)
			{
				stringstream ss;
				ss << "Texture" << idvalue.TextureIndex;
				i->second.get ()->BindToUniform (shader[ss.str()]);
			}
		}

		if ((*i).second.get()->GetType () == PermutationValueType::Constant)
		{
			i->second.get()->BindToUniform (shader[(*i).first]);
		}
			
	}
}

}}