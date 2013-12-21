#pragma once
#include <string>
namespace Tocs {

class Hashing
{	
public:
	Hashing() = delete;
	static unsigned int Hash (const std::string &string);
	static unsigned int HashInValue(unsigned int hash, unsigned int value);
};

}