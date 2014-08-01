#pragma once
#include <Tocs/Rendering/Material.h>
namespace Tocs {
namespace Voxels {

class VoxelShader : public Rendering::MaterialComponentSource
{
public:
	VoxelShader();

	VoxelShader(const VoxelShader &) = delete;

	VoxelShader &operator= (const VoxelShader &) = delete;

	static VoxelShader ParseFromConfig(const std::string &config);

	void LinkShaderCode(Rendering::ShaderConstruction &construction) const;
	Rendering::JobProxy QueueJob(Rendering::Geometry &geometry, Rendering::RenderSystem &pipeline) const;
};

}}


