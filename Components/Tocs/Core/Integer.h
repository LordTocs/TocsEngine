#pragma once
#include <string>
namespace Tocs {

class Integer
{
	Integer ();
	Integer (const Integer &);
public:
	static int Parse32 (const std::string &str);
	static short Parse16 (const std::string &str);
	static unsigned int ParseU32 (const std::string &str);
	static unsigned short ParseU16 (const std::string &str);
};

}