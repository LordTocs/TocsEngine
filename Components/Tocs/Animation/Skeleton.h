#pragma once
#include "Bone.h"
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/Buffer.h>
#include <vector>
namespace Tocs {
namespace Animation {


class SkeletonSource
{
	std::vector<BoneSource> Bones;
public:
	friend class Skeleton;
	SkeletonSource(const std::vector<BoneSource> &bones);
	unsigned int BoneCount() const { return Bones.size(); }
};


class Skeleton
{
	//Poses in object space
	const SkeletonSource* Source;
	std::vector<Math::Dual<Math::Quaternion>> Poses;
	std::vector<Bone> Bones;
public:
	

	Skeleton(const SkeletonSource &source);

	void ComputePoses();

	const std::vector<Math::Dual<Math::Quaternion>> &GetPoses() const { return Poses; }

	int IndexOfBone(const std::string &name) const;

	Bone &operator[](unsigned int index) { return Bones[index]; }
	const Bone &operator[](unsigned int index) const { return Bones[index]; }

	unsigned int BoneCount() const { return Bones.size(); }
};

}}

