#pragma once
#include <memory>
#include <string>
#include <map>
#include "PermutationValue.h"


namespace Tocs {
namespace Rendering {
namespace Permutations {

class PermutationValueSet
{
	std::map<std::string, std::unique_ptr<PermutationValue>> Values;
	
public:
	friend class PermutationID;

	PermutationValueSet () {}
	PermutationValueSet (const std::string &config);
	PermutationValueSet (const PermutationValueSet &copyme);
	PermutationValueSet (PermutationValueSet &&moveme);

	void Set (const std::string &valuename, PermutationValue *value)
	{
		Values[valuename] = std::unique_ptr <PermutationValue> (value);
	}

	std::map<std::string, std::unique_ptr<PermutationValue>>::iterator begin () { return Values.begin (); }
	std::map<std::string, std::unique_ptr<PermutationValue>>::iterator end () { return Values.end (); }

	std::map<std::string, std::unique_ptr<PermutationValue>>::const_iterator begin () const { return Values.begin (); }
	std::map<std::string, std::unique_ptr<PermutationValue>>::const_iterator end () const { return Values.end (); }
};


}}}