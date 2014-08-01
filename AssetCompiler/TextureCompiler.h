#pragma once
#include <Tocs/Graphics/TextureFormat.h>

namespace Tocs {
namespace AssetCompiler {

class TextureCompiler
{
public:
	bool Compressed;
	Graphics::TextureFiltering Filtering;

	void Compile(std::string &sourcefile, std::string &outfile);

};


}
}