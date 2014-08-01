#pragma once
#include <Tocs/Graphics/TextureFormat.h>

namespace Tocs {
namespace AssetCompiler {

class TextureCompiler
{
public:
	bool Compressed;
	Graphics::TextureFiltering Filtering;



	bool Compile(const std::string &sourcefile,const std::string &outfile);

};


}
}