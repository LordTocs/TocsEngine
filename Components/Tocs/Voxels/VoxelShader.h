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

	Rendering::Pipe &GetPipe(Rendering::RenderSystem &system) const;
	void LinkShaderCode(Rendering::ShaderConstruction &construction) const;
	void QueueJob(Rendering::JobProxy &proxy, Rendering::RenderSystem &system, Graphics::ShaderState &inputs) const;
};

}}


