#pragma once
#include <string>
namespace Tocs {

class Hashing
{	
	Hashing(void);
	~Hashing(void);
public:

	static unsigned int Hash (const std::string &string);
};

}