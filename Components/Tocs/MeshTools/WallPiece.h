#pragma once
#include <Tocs/Math/Vector3i.h>
#include "PolyLine.h"
namespace Tocs {
namespace MeshTools {

class WallPiece
{
	PolyLine &CrossSection;

	Math::Vector3i TL;
	Math::Vector3i TR;
	Math::Vector3i BR;

public:
	

	WallPiece (PolyLine &crossection)
		: CrossSection(crossection)
	{
	}

};

}}