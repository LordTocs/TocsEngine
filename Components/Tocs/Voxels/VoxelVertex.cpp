#include "VoxelVertex.h"

namespace Tocs {
namespace Voxels {

Graphics::VertexFormat VoxelVertex::InitFormat()
{
	Graphics::VertexFormat format;
	format.AddMember("Position", Graphics::GPUType::Vector3, false);
	format.AddMember("Normal", Graphics::GPUType::Vector3, true);
	format.AddMember("MaterialWeights", Graphics::GPUType::Vector3, false);
	format.AddMember("PrimIndex", Graphics::GPUType::UnsignedInt, false,false,true);
	return format;
}

FirstUseStatic <Graphics::VertexFormat, &VoxelVertex::InitFormat> VoxelVertex::Format;


}
}