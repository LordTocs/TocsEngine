#include "Hashing.h"
#include "city.h"

namespace Tocs {

unsigned int Hashing::Hash (const std::string &value)
{
	return CityHash32 (value.c_str (),value.size());
}

}