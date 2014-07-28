#include "Skeleton.h"
#include <cassert>
#include <Tocs/Math/DualQuaternionTransform.h>
#include <Tocs/Rendering/DebugDraw.h>
namespace Tocs {
namespace Animation {

SkeletonSource::SkeletonSource(const std::vector<BoneSource> &bones)
: Bones(bones)
{
	for (int i = 0; i < Bones.size(); ++i)
	{
		if (Bones[i].ParentIndex() != std::numeric_limits<unsigned int>::max())
		{
			assert(i > Bones[i].ParentIndex());
			//Bones[i].GlobalBindPose_ = Bones[Bones[i].ParentIndex()].GlobalBindPose_ * Bones[i].GlobalBindPose_;
		}
	}
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
		//std::cout << Bones[i].Name() << ": " << Bones[i].Transform.Position() << " " << Bones[i].Transform.Rotation() << " ";
		if (Bones[i].Parent() != std::numeric_limits<unsigned int>::max())
		{
			assert(i > Bones[i].Parent()); //This must be true.
			Poses[i] = Poses[Bones[i].Parent()] * Poses[i];


			Math::Vector3 ppos = Math::DualQuaternionTransform::ExtractPosition(Poses[Bones[i].Parent()]);
			Math::Vector3 pos = Math::DualQuaternionTransform::ExtractPosition(Poses[i]);

			//Math::Vector3 bppos = Math::DualQuaternionTransform::ExtractPosition(Bones[Bones[i].Parent()].GlobalBindPose());
			//Math::Vector3 bpos = Math::DualQuaternionTransform::ExtractPosition(Bones[i].GlobalBindPose());
			//
			//Math::Quaternion brot = Bones[i].GlobalBindPose().RealPart;

			Math::Quaternion rot = Poses[i].RealPart;
			

			Rendering::DebugDraw::Line(ppos, pos);
			
			Rendering::DebugDraw::Line(pos - rot.RotateVector(Math::Vector3(0, -0.5, 0)), pos + rot.RotateVector(Math::Vector3(0, -0.5, 0)));
			Rendering::DebugDraw::Line(pos - rot.RotateVector(Math::Vector3(-0.5, 0, 0)), pos + rot.RotateVector(Math::Vector3(-0.5, 0, 0)));
			Rendering::DebugDraw::Line(pos - rot.RotateVector(Math::Vector3(0, 0, -0.5)), pos + rot.RotateVector(Math::Vector3(0, 0, -0.5)));


			//Rendering::DebugDraw::Line(bppos, bpos, Math::Color(0,0,255));
			//Rendering::DebugDraw::Line(bpos - brot.RotateVector(Math::Vector3(0, -0.5, 0)), bpos + brot.RotateVector(Math::Vector3(0, -0.5, 0)), Math::Color(0, 0, 255));
			//Rendering::DebugDraw::Line(bpos - brot.RotateVector(Math::Vector3(-0.5, 0, 0)), bpos + brot.RotateVector(Math::Vector3(-0.5, 0, 0)), Math::Color(0, 0, 255));
			//Rendering::DebugDraw::Line(bpos - brot.RotateVector(Math::Vector3(0, 0, -0.5)), bpos + brot.RotateVector(Math::Vector3(0, 0, -0.5)), Math::Color(0, 0, 255));

			//std::cout << Poses[i].RealPart << "~" << Poses[i].DualPart;
		}
		//std::cout << std::endl;
	}


	//Create relative transforms from bind pose
	for (int i = 0; i < Bones.size(); ++i)
	{
		Math::Vector3 pos = Math::DualQuaternionTransform::ExtractPosition(Poses[i]);

		//Poses[i] = Poses[i] * Math::DualQuaternionTransform::Inverse(Bones[i].GlobalBindPose());
		Poses[i] = Poses[i] * Bones[i].BindPose();

		Math::Vector3 offset = Math::DualQuaternionTransform::ExtractPosition(Poses[i]);
		//Math::Vector3 bindpos = Math::DualQuaternionTransform::ExtractPosition(Bones[i].GlobalBindPose());

		//Rendering::DebugDraw::Line(bindpos, pos, Math::Color(255,0,0));

	}
}

}}
