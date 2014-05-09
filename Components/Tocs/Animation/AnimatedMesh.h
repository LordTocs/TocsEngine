#pragma once
#include <Tocs/Rendering/Mesh.h>
#include "Skeleton.h"

namespace Tocs {
namespace Animation {

class AnimatedMesh
{
	Rendering::Mesh Mesh_;
	SkeletonSource Armature_;
public:
	AnimatedMesh(Rendering::Mesh &&mesh, SkeletonSource &&armature);
	AnimatedMesh(AnimatedMesh &&moveme);

	AnimatedMesh(const AnimatedMesh &) = delete;
	AnimatedMesh &operator= (const AnimatedMesh &) = delete;
	AnimatedMesh &operator= (AnimatedMesh &&);

	const Rendering::Mesh &Mesh() const { return Mesh_; }
	const SkeletonSource &Armature() const { return Armature_; }

	static AnimatedMesh LoadFromFile(const std::string &filename);

};

}}