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
	  LinearDepth (system.Context().GetTarget().GetWidth(), system.Context().GetTarget().GetHeight(), TextureFiltering::None, TextureFormat::R32)
{
	Target.SetTexture (Albedo,0);
	Target.SetTexture (Normals,1);
	Target.SetTexture (Specular,2);
	Target.SetTexture (LinearDepth,3);
	Target.SetDepthBuffer(system.FrameDepth);
}

void GBuffer::Bind ()
{
	Target.Bind ();
}

void GBuffer::UnBind ()
{
	Target.UnBind ();
}

void GBuffer::DoLighting (RenderSystem &system)
{
	static Asset<Graphics::Shader> DefPointLight = Asset<Graphics::Shader>::Load("shaders/deferred/PointLight.shd");

	for (auto &l : system.GetLights())
	{
		if (!l->Visible())
			continue;

	}
}

}}