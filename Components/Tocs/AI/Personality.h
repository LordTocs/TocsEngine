#pragma once
#include <string>
#include <vector>
#include <Tocs/Math/Util.h>

namespace Tocs {
namespace AI {


class PersonalityAttributeBase
{
	std::string Name_;
	unsigned int Index_;
public:
	PersonalityAttributeBase(const std::string &name)
		: Name_(name), Index_(0){}
	const std::string &Name() const { return Name_; }
	unsigned int Index() const { return Index_; }

	friend class PersonalitySetBase;
};
//[-1,1]
class PersonalityAttribute
{
	const PersonalityAttributeBase *Base;
	float Value_;
public:
	PersonalityAttribute(const PersonalityAttributeBase &base);
	const std::string &Name() const { return Base->Name(); }
	const float &Value() const { return Value_; }
};

class PersonalitySetBase
{
	std::vector<PersonalityAttributeBase> Attributes;
public:
	void AddAttribute(const std::string &name);
	int GetAttributeIndex(const std::string &name) const;
	void Finalize();
	friend class PersonalitySet;
};

class PersonalitySet
{
	const PersonalitySetBase *Base;
	std::vector<PersonalityAttribute> Attributes;
public:
	PersonalitySet(const PersonalitySetBase &base);

	int GetAttributeIndex(const std::string &name) const;

	PersonalityAttribute &GetAttribute(unsigned int index) { return Attributes[index]; }
	const PersonalityAttribute &GetAttribute(unsigned int index) const { return Attributes[index]; }
};

}}