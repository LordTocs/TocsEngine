#include "PermutationValue.h"
namespace Tocs {
namespace Rendering {
namespace Permutations {

void TextureValue::FillValueInfo (std::vector<Asset<Graphics::Texture2D>> &textures, PermutationID::ValueInfo &info)
{
	info.Component = 'x';
	info.Type = PermutationValueType::Map;
	for (int i = 0; i < textures.size (); ++i)
	{
		if (textures[i] == Texture)
		{
			info.TextureIndex = i;
			return;
		}
	}
	info.BinderValue = true;
	textures.push_back(Texture);
	info.TextureIndex = textures.size () - 1;
	
}

void TextureComponentValue::FillValueInfo (std::vector<Asset<Graphics::Texture2D>> &textures, PermutationID::ValueInfo &info)
{
	info.Component = Component;
	info.Type = PermutationValueType::MapComponent;
	for (int i = 0; i < textures.size (); ++i)
	{
		if (textures[i] == Texture)
		{
			info.TextureIndex = i;
			return;
		}
	}

	info.BinderValue = true;
	textures.push_back(Texture);
	info.TextureIndex = textures.size () - 1;
	
}


}}}