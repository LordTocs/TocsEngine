#pragma once
#include "Enums.h"
namespace Tocs {
namespace Voxels {


class Voxel
{
public:
	struct VoxelInfo
	{
		unsigned char Direction : 3;
		unsigned char Fill : 5;
	};
	VoxelInfo Info;

	bool IsFilled () const { return Info.Fill == 31; }
	bool IsEmpty () const { return Info.Fill == 0; }

	FaceType GetFaceState (Direction direction) const;

	Direction GetDirection () const { return Direction::FromIndex(Info.Direction); }
};

}}

