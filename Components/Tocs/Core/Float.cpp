#include "Float.h"

namespace Tocs {

float Float::Parse (const std::string &str)
{
	return atof (str.c_str ());
}

}