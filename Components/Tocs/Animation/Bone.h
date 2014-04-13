#pragma once
#include <string>
#include <Tocs/Math/Transform.h>
namespace Tocs {
namespace Animation {

class BoneSource
{
	std::string Name_;
	unsigned int ParentIndex_;
public:
	const std::string &Name() const { return Name_; }
	unsigned int ParentIndex() const { return ParentIndex_; }
};

class Bone
{
	const BoneSource *Source;
	unsigned int ParentIndex;
public:
	Bone(BoneSource &Source);
	Math::Transform Transform;
};

}}
