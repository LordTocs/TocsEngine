#include "Hashing.h"
#include "city.h"

namespace Tocs {

unsigned int Hashing::Hash (const std::string &value)
{
	return CityHash32 (value.c_str (),value.size());
}

unsigned int Hashing::HashInValue(unsigned int hash, unsigned int value)
{
	return value + (hash << 6) + (hash << 16) - hash;
}

}