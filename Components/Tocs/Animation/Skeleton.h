#pragma once
#include "Bone.h"
#include <vector>
namespace Tocs {
namespace Animation {


class SkeletonSource
{
	std::vector<BoneSource> Bones;
public:
	friend class Skeleton;
};


class Skeleton
{
	//Poses in object space
	std::vector<Math::Dual<Math::Quaternion>> Poses;
	std::vector<Bone> Bones;
public:
	Skeleton(SkeletonSource &source);

	void ComputePoses();
};

}}

