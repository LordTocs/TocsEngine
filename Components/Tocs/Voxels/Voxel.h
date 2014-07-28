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
		unsigned char Id;
	};
	VoxelInfo Info;

	bool IsFilled () const { return Info.Fill == 31; }
	bool IsEmpty () const { return Info.Fill == 0; }
	bool IsPartial() const { return Info.Fill != 0 && Info.Fill != 31; }

	Math::Vector3i Localize(const Math::Vector3i &vector) const;
	Math::Vector3 Globalize(const Math::Vector3 &vector) const;

	float FillNorm() const { return Info.Fill / 31.0f; }

	Direction GetDirection () const { return Direction::FromIndex(Info.Direction); }
	void SetDirection(const Direction &direction) { Info.Direction = direction.Index(); }

	void Set(unsigned char fill, Direction direction);


	static unsigned int GetCorrespondingPoint(unsigned int point, Direction dir, Math::Vector3i offset, Direction otherdir);
};

}}

