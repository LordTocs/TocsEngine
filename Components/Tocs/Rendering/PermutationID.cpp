#include "PermutationID.h"
#include <vector>
#include "ShaderPermutator.h"
#include "PermutationValue.h"
#include "PermutationValueSet.h"

#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/Texture.h>



using namespace std;

namespace Tocs {
namespace Rendering {
namespace Permutations {


PermutationID::PermutationID(ShaderPermutator &permutator, PermutationValueSet &values)
	: TextureCount (0)
{   
	for (auto i = permutator.Template.Fields.begin (); i != permutator.Template.Fields.end (); ++i)
	{
		ValueTypes[(*i).first] = ValueInfo ((*i).second.GetType ());
	}

	vector<Asset<Graphics::Texture2D>> textures;

	for (auto i = values.Values.begin (); i != values.Values.end (); ++i)
	{
		(*i).second->FillValueInfo (textures,ValueTypes[(*i).first]);
	}

	TextureCount = textures.size ();

}

bool PermutationID::operator< (const PermutationID &op2) const
{
	if (!(TextureCount < op2.TextureCount))
	{
		return false;
	}

	for (auto i = ValueTypes.begin (), j = op2.ValueTypes.begin (); i != ValueTypes.end () && j != op2.ValueTypes.end (); ++i,++j)
	{
		if (!((*i).second < (*j).second))
			return false;
	}

	return true;
}

bool PermutationID::ValueInfo::operator< (const PermutationID::ValueInfo &op2) const
{
	if (!(VarType < op2.VarType))
	{
		return false;
	}

	if (!(TextureIndex < op2.TextureIndex))
	{
		return false;
	}

	if (!(Component < op2.Component))
	{
		return false;
	}

	if (!(Type < op2.Type))
	{
		return false;
	}

	return true;
}


}}}