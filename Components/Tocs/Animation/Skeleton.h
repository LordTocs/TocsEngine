#pragma once
#include "Bone.h"
#include <vector>
namespace Tocs {
namespace Animation {


class SkeletonSource
{
	std::vector<BoneSource> Bones;
public:

};


class Skeleton
{
	std::vector<Math::Dual<Math::Quaternion>> Poses;
	std::vector<Bone> Bones;
public:
	Skeleton(SkeletonSource &source);
};

}}

