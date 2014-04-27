#pragma once
#include <string>
#include <Tocs/Math/Transform.h>
namespace Tocs {
namespace Animation {

class BoneSource
{
	std::string Name_;
	unsigned int ParentIndex_;
	Math::Dual<Math::Quaternion> BindPose_;
public:
	const std::string &Name() const { return Name_; }
	unsigned int ParentIndex() const { return ParentIndex_; }
	const Math::Dual<Math::Quaternion> &BindPose() const { return BindPose_; }
};

class Bone
{
	const BoneSource *Source;
	unsigned int ParentIndex;
public:
	Bone(BoneSource &Source);
	Math::Transform Transform;

	unsigned int Parent() const { return ParentIndex; }
};

}}
