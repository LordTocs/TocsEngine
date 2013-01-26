#include "Material.h"
#include <iostream>
#include <sstream>
#include <Tocs/Core/Tokenizer.h>
#include <Tocs/Core/Character.h>
#include "DeferredMaterial.h"
#include <assert.h>
using namespace std;
using namespace Tocs::Lexing;

namespace Tocs {
namespace Rendering {

/*Material::Material (const Material &copyme)
{
	for (auto i = copyme.Passes.begin (); i != copyme.Passes.end (); ++i)
	{
		Passes.push_back (std::unique_ptr<MaterialPass> ((*i)->Clone ()));
	}
}*/

Material::Material (Material &&moveme)
	: Passes(std::move(moveme.Passes))
{
}

Material Material::LoadFromFile (const std::string &filename)
{
	StringSource source = StringSource::FromFile(filename);
	Tokenizer tokens (source);
	Material result;
	
	while (!tokens.EndOfStream ())
	{
		string name = tokens.GetToken ();
		string config = tokens.GetTextIn ("{","}");
		if (name == "DeferredMaterial")
		{
			result.Passes.push_back(std::move(std::unique_ptr<MaterialPass>(new DeferredMaterial (config))));
		}
	}

	return std::move(result);
	
}

}}