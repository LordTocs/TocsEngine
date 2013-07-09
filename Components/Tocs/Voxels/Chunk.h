#pragma once

#include "Voxel.h"
#include <Tocs/Rendering/Mesh.h>
#include <Tocs/MeshTools/MeshBuilder.h>
#include <Tocs/Rendering/Vertices.h>
#include <Tocs/Math/Vector3i.h>
namespace Tocs {
namespace Voxels {

class Chunk
{
	Voxel Voxels[4096];//16x16x16
	void FillFace (const Math::Vector3i &pos, const Direction &dir, MeshTools::MeshBuilder<Rendering::PositionTextureNormal> &builder);
	void Voxelize (const Math::Vector3i &pos, MeshTools::MeshBuilder<Rendering::PositionTextureNormal> &builder);
public:
	std::unique_ptr <Rendering::Mesh> GeneratedMesh;
	Chunk();

	bool InBounds (int x, int y, int z) const;
	bool InBounds (const Math::Vector3i &pos) const;
	inline Voxel &Get(int x, int y, int z) { return Voxels[x + z * 16 + y * 256]; }
	inline Voxel &Get(const Math::Vector3i &pos) { return Voxels[pos.X + pos.Y * 16 + pos.Z * 256]; }
	inline const Voxel &Get(int x, int y, int z) const { return Voxels[x + z * 16 + y * 256]; }
	inline const Voxel &Get(const Math::Vector3i &pos) const { return Voxels[pos.X + pos.Y * 16 + pos.Z * 256]; }

	void GenerateMesh ();
	

};

}}
