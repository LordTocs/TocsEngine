#include "Skeleton.h"
#include <cassert>
namespace Tocs {
namespace Animation {

SkeletonSource::SkeletonSource(const std::vector<BoneSource> &bones)
: Bones(bones)
{

}

Skeleton::Skeleton(const SkeletonSource &source)
: Source(&source)
{
	Bones.reserve(source.Bones.size());
	Poses.reserve(source.Bones.size());
	for (auto &bs : source.Bones)
	{
		Bones.emplace_back(bs);
		if (bs.ParentIndex() != std::numeric_limits<unsigned int>::max())
		{
			Bones.rbegin()->Transform.Parent(Bones[bs.ParentIndex()].Transform);
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
		std::cout << Bones[i].Name() << ": " << Bones[i].Transform.Position() << " " << Bones[i].Transform.Rotation() << " ";
		if (Bones[i].Parent() != std::numeric_limits<unsigned int>::max())
		{
			assert(i > Bones[i].Parent()); //This must be true.
			Poses[i] = Poses[Bones[i].Parent()] * Poses[i];
			std::cout << Poses[i].RealPart << "~" << Poses[i].DualPart;
		}

		std::cout << std::endl;
	}


	//Create relative transforms from bind pose
	for (int i = 0; i < Bones.size(); ++i)
	{
		Poses[i] = Poses[i] * Bones[i].BindPose().Conjugate();
		std::cout << std::endl;
	}
}

}}
