#include <iostream>
#include "ShaderPermutator.h"

using namespace std;
using namespace Tocs::Graphics;


namespace Tocs {
namespace Rendering {

ShaderPermutator::ShaderPermutator (const std::string &filename)
	: Template (filename)
{}

ShaderPermutator::ShaderPermutator (ShaderPermutator &&moveme)
	: Template(std::move(moveme.Template))
{}

Permutation &ShaderPermutator::GetPermutation (Permutations::PermutationValueSet &values)
{
	Permutations::PermutationID id (*this,values);
	
	auto pixeli = Permutations.find (id);
	if (pixeli == Permutations.end ())
	{
		//Pixel Shader Permutation not generated
		const std::string &shaderscript = Template.GetScript (id);
		ShaderCode code (ShaderType::Pixel);
		code.Compile (shaderscript);
		if (!code.Compiled ())
		{
			cout << "Pixel Shader permutation failed: " << endl
				 << code.GetCompileErrors () << endl;

			throw "Pixel Permutation Failed";
		}

		pixeli = Permutations.insert (make_pair (id,Permutation (id,std::move(code)))).first;
	}

	return (*pixeli).second;

}

ShaderPermutator ShaderPermutator::LoadFromFile (const std::string &filename)
{
	return ShaderPermutator(filename);
}


}}