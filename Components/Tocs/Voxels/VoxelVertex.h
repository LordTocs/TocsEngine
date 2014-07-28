#pragma once
#include <Tocs/Math/Vector.h>
#include <Tocs/Graphics/VertexFormat.h>
#include <Tocs/Core/LateStatic.h>

namespace Tocs {
namespace Voxels {


class VoxelVertex
{
public:
	Math::Vector3 Position;
	Math::Vector3 Normal;
	Math::Vector4 MaterialWeights;
	unsigned int PrimIndex;

	static Graphics::VertexFormat InitFormat();
	static FirstUseStatic <Graphics::VertexFormat, &InitFormat> Format;
};


}
}