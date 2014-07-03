#pragma once
#include <string>
#include <Tocs/Math/Transform.h>
namespace Tocs {
namespace Animation {

class BoneSource
{
	std::string Name_;
	unsigned int ParentIndex_;
	Math::Dual<Math::Quaternion> DefaultPose_;
	Math::Dual<Math::Quaternion> BindPose_;
	//Math::Dual<Math::Quaternion> GlobalBindPose_;
public:
	BoneSource(const std::string &name, unsigned int pdx, Math::Dual<Math::Quaternion> defpos,Math::Dual<Math::Quaternion> bind)
		: Name_(name), ParentIndex_(pdx), BindPose_(bind), DefaultPose_(defpos)/*, GlobalBindPose_(bind)*/ {}

	const std::string &Name() const { return Name_; }
	unsigned int ParentIndex() const { return ParentIndex_; }
	const Math::Dual<Math::Quaternion> &DefaultPose() const { return DefaultPose_; }
	const Math::Dual<Math::Quaternion> &BindPose() const { return BindPose_; }
	//const Math::Dual<Math::Quaternion> &GlobalBindPose() const { return GlobalBindPose_; }

	friend class SkeletonSource;
	friend class AnimatedMesh;
};

class Bone
{
	const BoneSource *Source;
	unsigned int ParentIndex;
public:
	Bone(const BoneSource &source)
	: Source(&source), ParentIndex(source.ParentIndex())
	{
		Transform.FromDualQuaternion(source.DefaultPose());
	}

	Math::Transform Transform;

	unsigned int Parent() const { return ParentIndex; }
	const std::string &Name() const { return Source->Name(); }
	const Math::Dual<Math::Quaternion> &DefaultPose() const { return Source->DefaultPose(); }
	const Math::Dual<Math::Quaternion> &BindPose() const { return Source->BindPose(); }
	//const Math::Dual<Math::Quaternion> &GlobalBindPose() const { return Source->GlobalBindPose(); }
};

}}
