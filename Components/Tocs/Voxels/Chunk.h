#pragma once

#include "Voxel.h"
#include <Tocs/Rendering/Mesh.h>
#include <Tocs/MeshTools/MeshBuilder.h>
#include <Tocs/Rendering/Vertices.h>
#include <Tocs/Math/Vector.h>
namespace Tocs {
namespace Voxels {

class Chunk
{
	Voxel Voxels[4096];//16x16x16
	void FillFace (const Math::Vector3i &pos, const Direction &dir, MeshTools::MeshBuilder<Rendering::PositionTextureNormal> &builder);
	void Voxelize (const Math::Vector3i &pos, MeshTools::MeshBuilder<Rendering::PositionTextureNormal> &builder);

	class PointInfo
	{
	public:

		//One of the neighbors require's a vertice at the top
		bool HasTop;
		//One of the neighbors require's a vertice at the bottom
		bool HasBottom;
		//If there's no top or bottom and this flag is set then the vertice matches the average fill of the neighbors
		unsigned int FillAverageCount;
		float FillSum;

		//Offset in voxelspace of a vertice to smooth to a voxel "on top" of it.
		Math::Vector3 Offset;

		PointInfo()
			: HasTop(false), HasBottom(false), FillAverageCount(0), FillSum(0) {}
	};

	void AdjustOffset(const Math::Vector3i &pos, const Math::Vector3i &vertoffset, PointInfo &result) const;
	void CollectNeighborInfo(const Math::Vector3i &pos, const Math::Vector3i &offset, const Math::Vector3i &vertoffset, PointInfo &result) const;
	PointInfo GetPointInfo(const Math::Vector3i &pos, unsigned int index) const;
public:
	std::unique_ptr <Rendering::Mesh> GeneratedMesh;
	Chunk();

	bool InBounds (int x, int y, int z) const;
	bool InBounds (const Math::Vector3i &pos) const;
	inline Voxel &Get(int x, int y, int z) { return Voxels[x + z * 16 + y * 256]; }
	inline Voxel &Get(const Math::Vector3i &pos) { return Voxels[pos.X + pos.Z * 16 + pos.Y * 256]; }
	inline const Voxel &Get(int x, int y, int z) const { return Voxels[x + z * 16 + y * 256]; }
	inline const Voxel &Get(const Math::Vector3i &pos) const { return Voxels[pos.X + pos.Z * 16 + pos.Y * 256]; }

	void GenerateMesh ();
	

};

}}
