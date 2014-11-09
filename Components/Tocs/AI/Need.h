#pragma once
#include <string>
#include <vector>
#include <Tocs/Math/Util.h>
namespace Tocs {
namespace AI {

class NeedBase
{
	std::string Name_;
	unsigned int Index_;
public:
	NeedBase(const std::string name)
		: Name_(name), Index_(0) {}
	const std::string &Name() const { return Name_; }
	unsigned int Index() const { return Index_; }

	friend class NeedSetBase;
};

//[0,1]
class Need
{
	const NeedBase *Base;
	float Value_;
public:
	Need(const NeedBase &base);
	const std::string &Name() const { return Base->Name(); }
	const float &Value() const { return Value_; }

	void Value(float value) { Value_ = Math::Clamp(value, 0.0f, 1.0f); }
	void OffsetValue(float offset) { Value_ = Math::Clamp(Value_ + offset, 0.0f, 1.0f); }
};

class NeedSetBase
{
	std::vector<NeedBase> Needs;
public:
	void AddNeed(const std::string &name);
	int GetNeedIndex(const std::string &name) const;
	void Finalize();

	friend class NeedSet;
};

class NeedSet
{
	const NeedSetBase *Base;
	std::vector<Need> Needs;
public:
	NeedSet(const NeedSetBase &base);

	int GetNeedIndex(const std::string &name) const;

	Need &GetAttribute(unsigned int index) { return Needs[index]; }
	const Need &GetAttribute(unsigned int index) const { return Needs[index]; }
};

}
}
