#include "GBuffer.h"
#include "RenderSystem.h"
#include <Tocs/Graphics/TextureFormat.h>

using namespace Tocs::Graphics;

namespace Tocs {
namespace Rendering {

GBuffer::GBuffer(RenderSystem &system)
	: Albedo      (system.Context().GetTarget().GetWidth(), system.Context().GetTarget().GetHeight(), TextureFiltering::None, TextureFormat::RGBA8),
	  Normals     (system.Context().GetTarget().GetWidth(), system.Context().GetTarget().GetHeight(), TextureFiltering::None, TextureFormat::RGBA8),
	  Specular    (system.Context().GetTarget().GetWidth(), system.Context().GetTarget().GetHeight(), TextureFiltering::None, TextureFormat::RGBA8),
	  LinearDepth (system.Context().GetTarget().GetWidth(), system.Context().GetTarget().GetHeight(), TextureFiltering::None, TextureFormat::R32),
	  LightingShader(Asset<Graphics::Shader>::Load("shaders/deferred/DeferredShading.shd")),
	  ShadingSet(LightingShader.Get())
{
	Target.SetTexture (Albedo,0);
	Target.SetTexture (Normals,1);
	Target.SetTexture (Specular,2);
	Target.SetTexture (LinearDepth,3);
	Target.SetDepthBuffer(system.FrameDepth);

	DeferredBuffers.AddValue("ColorBuffer").Ref(Albedo);
	DeferredBuffers.AddValue("NormalBuffer").Ref(Normals);
	DeferredBuffers.AddValue("SpecularBuffer").Ref(Specular);
	DeferredBuffers.AddValue("DepthBuffer").Ref(LinearDepth);

	ShadingSet.MapState(DeferredBuffers);
	ShadingSet.MapState(system.GetLightTiles().GetShaderInputs());
}

void GBuffer::Bind ()
{
	Target.Bind ();
}

void GBuffer::UnBind ()
{
	Target.UnBind ();
}

void GBuffer::DoLighting (Graphics::GraphicsContext &context, RenderSystem &system, const Camera &camera)
{
	LightingShader->Bind();
	ShadingSet.BindAll();
	(*LightingShader)["InvProjection"] = camera.GetInverseProjection();
	Quad.PushGeometry(context);
	LightingShader->UnBind();
}

}}