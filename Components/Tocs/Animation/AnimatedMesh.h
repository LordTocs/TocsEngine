#pragma once
#include <Tocs/Rendering/Mesh.h>
#include <Tocs/Rendering/Vertices.h>
#include <memory>
#include "Skeleton.h"

struct aiScene;
struct aiNode;

namespace Tocs {
namespace Animation {

class AnimatedMesh
{
	Rendering::Mesh Mesh_;
	SkeletonSource Armature_;
	//Loading helper
	static void LoadMesh(const aiScene *scene, aiNode *node, int &vertdex, int &indexdex, std::unique_ptr<Rendering::PositionTextureNormalTangentBone[]> &verts, std::unique_ptr<unsigned int[]> &indices, std::vector<BoneSource> &bones, std::map<std::string, unsigned int> &bonemapping, Rendering::Mesh &rmesh, Math::Matrix4 transform);
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