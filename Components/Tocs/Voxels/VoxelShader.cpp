#include "VoxelShader.h"
#include <Tocs/Rendering/TransparencyType.h>
#include <Tocs/Rendering/RenderSystem.h>
namespace Tocs {
namespace Voxels {

void VoxelShader::LinkShaderCode(Rendering::ShaderConstruction &construction) const
{
	static Asset<Graphics::ShaderCode> evaluator = Asset<Graphics::ShaderCode>::Load("shaders/TileShadingEvaluator.frag");

	construction.AddCode(evaluator.Get());
	construction.AddCode(Rendering::TransparencyType::Opaque.GetCompositor());
}

Rendering::Pipe &VoxelShader::GetPipe(Rendering::RenderSystem &system) const
{
	return system.Pipes.OpaquePipe;
}

void VoxelShader::QueueJob(Rendering::JobProxy &proxy, Rendering::RenderSystem &system, Graphics::ShaderState &inputs) const
{
	proxy.Get().StateSet.MapState(system.GetLightTiles().GetShaderInputs());
	proxy.Get().StateSet.MapState(system.GetShadows().GetShaderInputs());
}


}
}