#pragma once
#include <string>
namespace Tocs {

class Float
{
	Float();
	Float(const Float &);
public:
	static float Parse (const std::string &str);
};

}