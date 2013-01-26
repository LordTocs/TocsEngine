#include "Integer.h"

using namespace std;

namespace Tocs {

int Integer::Parse32 (const std::string &str)
{
	return atoi (str.c_str ());
}
short Integer::Parse16 (const std::string &str)
{
	return static_cast<short>(atoi(str.c_str ()));
}
unsigned int Integer::ParseU32 (const std::string &str)
{
	return static_cast<unsigned int> (atol(str.c_str ()));
}
unsigned short Integer::ParseU16 (const std::string &str)
{
	return static_cast<unsigned short> (atoi(str.c_str ()));
}

}