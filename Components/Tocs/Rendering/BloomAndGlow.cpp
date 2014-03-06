#include "BloomAndGlow.h"
#include "RenderSystem.h"
namespace Tocs {
namespace Rendering {

BloomAndGlow::BloomAndGlow(RenderSystem &system)
: GlowBufferA(system.Context().GetTarget().GetWidth(), system.Context().GetTarget().GetHeight(),Tocs::Graphics::TextureFiltering::None,Graphics::TextureFormat::RGB8)
, GlowBufferB(system.Context().GetTarget().GetWidth(), system.Context().GetTarget().GetHeight(), Tocs::Graphics::TextureFiltering::None, Graphics::TextureFormat::RGB8)
, GlowDepthBuffer(system.Context().GetTarget().GetWidth(), system.Context().GetTarget().GetHeight(),Graphics::DepthStencilFormat::D32S8)
, Blur(Asset<Graphics::Shader>::Load("shaders/glow/blur.shd"))
, Composite(Asset<Graphics::Shader>::Load("shaders/glow/composite.shd"))
, DownsampleDepth(Asset<Graphics::Shader>::Load("shaders/glow/downsampledepth.shd"))
, PostProcess(system)
{
	GlowTargetA.Bind();
	GlowTargetA.SetTexture(GlowBufferA, 0);
	GlowTargetA.SetDepthBuffer(GlowDepthBuffer);
	//GlowTargetA.SetDepthBuffer(system.FrameDepth);
	GlowTargetA.UnBind();

	GlowTargetB.Bind();
	GlowTargetB.SetTexture(GlowBufferB, 0);
	//GlowTargetB.SetDepthBuffer(GlowDepthBuffer);
	GlowTargetB.UnBind();
}

void BloomAndGlow::SetupGlowViewport(Graphics::GraphicsContext &context)
{
	context.Viewport(GlowBufferA.Width(), GlowBufferA.Height());
}

void BloomAndGlow::ConvertDepthBuffer()
{
	DownsampleDepth.Get().Bind();
	DownsampleDepth.Get()["Depth"] = System->FrameDepth;
	Quad.PushGeometry(System->Context());
	DownsampleDepth.Get().UnBind();
}

void BloomAndGlow::Apply(const Graphics::Texture2D &sourcetexture, Graphics::RenderTarget &target)
{
	int amount = 10;
	float str = 1.6f;
	float scale = 1.0;
	SetupGlowViewport(System->Context());

	GlowTargetB.Bind();
	Blur.Get().Bind();
	Blur.Get()["TexelSize"] = Math::Vector2(float(1) / (GlowBufferA.Width()), float(1) / (GlowBufferA.Height()));
	Blur.Get()["BlurSource"] = GlowBufferA;
	Blur.Get()["Orientation"] = 0; //horizontal
	Blur.Get()["BlurAmount"] = amount;
	Blur.Get()["BlurScale"] = scale;
	Blur.Get()["BlurStrength"] = str;
	Quad.PushGeometry(System->Context());
	Blur.Get().UnBind();
	GlowTargetB.UnBind();
	
	GlowTargetA.Bind();
	Blur.Get().Bind();
	Blur.Get()["TexelSize"] = Math::Vector2(float(1) / (GlowBufferA.Width()), float(1) / (GlowBufferA.Height()));
	Blur.Get()["BlurSource"] = GlowBufferB;
	Blur.Get()["Orientation"] = 1; //verticle
	Blur.Get()["BlurAmount"] = amount;
	Blur.Get()["BlurScale"] = scale;
	Blur.Get()["BlurStrength"] = str;
	Quad.PushGeometry(System->Context());
	Blur.Get().UnBind();
	GlowTargetA.UnBind();

	System->Context().Viewport(System->Context().GetTarget().GetWidth(), System->Context().GetTarget().GetHeight());

	target.Bind();
	Composite.Get().Bind();
	Composite.Get()["Destination"] = sourcetexture;
	Composite.Get()["BlurMap"] = GlowBufferA;
	Composite.Get()["BlendMode"] = 1;
	Quad.PushGeometry(System->Context());
	Composite.Get().UnBind();
	target.UnBind();
}

void BloomAndGlow::OutputDebugImages(std::string filebase)
{
	GlowBufferA.SaveDebug(filebase + std::string("a.png"));
	GlowBufferB.SaveDebug(filebase + std::string("b.png"));
}


}}