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

Rendering::JobProxy VoxelShader::QueueJob(Rendering::Geometry &geometry, Rendering::RenderSystem &system) const
{
	Rendering::ShaderConstruction construction;
	LinkShaderCode(construction);
	geometry.LinkShaders(construction, false);

	Rendering::JobProxy proxy;
	proxy = system.Pipes.OpaquePipe.Add(geometry.GetCall(), construction.Link(Rendering::ShaderPool::Global));
	proxy.Get().Input.ApplyMap(system.GetLightTiles().GetShaderInputs());
	proxy.Get().Input["ShadowMaps"].Ref(system.GetShadows().GetShadowMaps());
	return proxy;
}


}
}