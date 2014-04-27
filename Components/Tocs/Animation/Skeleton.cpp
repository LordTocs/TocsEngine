#include "Skeleton.h"
#include <cassert>
namespace Tocs {
namespace Animation {

Skeleton::Skeleton(SkeletonSource &source)
{
	Bones.reserve(source.Bones.size());
	Poses.reserve(source.Bones.size());
	for (auto &bs : source.Bones)
	{
		Bones.emplace_back(bs);
		if (bs.ParentIndex != std::numeric_limits<unsigned int>::max())
		{
			Bones.rbegin()->Transform.Parent(Bones[bs.ParentIndex].Transform());
		}
		Poses.push_back(Math::Dual <Math::Quaternion> ());
	}
}

void Skeleton::ComputePoses()
{
	//Bones are in sorted order of their tree depth, parent bone poses guarenteed to be complete
	for (int i = 0; i < Bones.size(); ++i)
	{
		Poses[i] = Bones[i].Transform.ToDualQuaterion();
		if (Bones[i].Parent() != std::numeric_limits<unsigned int>::max())
		{
			assert(i > Bones[i].Parent()); //This must be true.
			Poses[i] = Poses[Bones[i].Parent()] * Poses[i];
		}
	}
}

}}
