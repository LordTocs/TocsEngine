#include "ABuffer.h"
#include "RenderSystem.h"
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/Shader.h>

namespace Tocs {
namespace Rendering {

ABuffer::ABuffer(RenderSystem &system)
: Semaphore (system.Context().GetTarget().GetWidth(), system.Context().GetTarget().GetHeight(),Graphics::TextureFiltering::None,Graphics::TextureFormat::R32ui)
, PageIndices (system.Context().GetTarget().GetWidth(), system.Context().GetTarget().GetHeight(), Graphics::TextureFiltering::None, Graphics::TextureFormat::R32ui)
, FragCount(system.Context().GetTarget().GetWidth(), system.Context().GetTarget().GetHeight(), Graphics::TextureFiltering::None, Graphics::TextureFormat::R32ui)
, PageCount(100)
, PageSize(8)
, ColorPageBuffer(PageCount*PageSize)
, DepthPageBuffer(PageCount*PageSize)
, ModePageBuffer(PageCount*PageSize)
, PageLinkBuffer(PageCount)
, AtomicPageCounter(1)
, PageLinks(PageLinkBuffer, Graphics::TextureFormat::R32ui)
, ColorPages(ColorPageBuffer,Graphics::TextureFormat::RGBA8)
, DepthPages(DepthPageBuffer, Graphics::TextureFormat::R32)
, ModePages(ModePageBuffer, Graphics::TextureFormat::R8ui)
{
	AtomicPageCounter.Write({ 1 });

	Inputs["ABufferIndex"].Ref(PageIndices);
	Inputs["ABufferCounts"].Ref(FragCount);
	Inputs["ABufferSemaphore"].Ref(Semaphore);
	Inputs["PageLinks"].Ref(PageLinks);
	Inputs["ColorPages"].Ref(ColorPages);
	Inputs["DepthPages"].Ref(DepthPages);
	Inputs["ModePages"].Ref(ModePages);
	Inputs["MaxPageCount"].Ref(PageCount);


	std::cout << "ABufferIndex: " << PageIndices.GetID() << std::endl;
	std::cout << "ABufferCounts: " << FragCount.GetID() << std::endl;
	std::cout << "ABufferSemaphore: " << Semaphore.GetID() << std::endl;
	std::cout << "PageLinks: " << PageLinks.GetID() << std::endl;
}

void ABuffer::Bind()
{
	AtomicPageCounter.BindTo(Graphics::BufferTarget::AtomicCounter, 0);
	SampleQuery.Begin(Graphics::QueryTarget::SamplesPassed);
}

void ABuffer::UnBind()
{
	AtomicPageCounter.UnBind();
	SampleQuery.End();
}

void ABuffer::BlendAndPresent(RenderSystem &system)
{
	static Asset<Graphics::Shader> blender = Asset<Graphics::Shader>::Load("shaders/transparency/blending.shd");

	//std::vector< unsigned int> links;
	//PageLinkBuffer.Read(links);

	system.Context().AlphaBlending();
	system.Context().DisableDepthTest();
	system.Context().DisableDepthWrite();

	blender.Get().Bind();

	blender.Get()["ABufferIndex"] = PageIndices;
	blender.Get()["ABufferCounts"] = FragCount;
	blender.Get()["PageLinks"] = PageLinks;

	blender.Get()["ColorPages"] = ColorPages;
	blender.Get()["DepthPages"] = DepthPages;
	blender.Get()["ModePages"] = ModePages;

	blender.Get()["ScreenSize"] = Math::Vector2ui(system.Context().GetTarget().GetWidth(), system.Context().GetTarget().GetHeight());
	Quad.PushGeometry(system.Context());

	blender.Get().UnBind();

	system.Context().NormalBlending();
	system.Context().EnableDepthTest();
	system.Context().EnableDepthWrite();
}

void ABuffer::Clear(RenderSystem &system)
{
	static Asset<Graphics::Shader> clearer = Asset<Graphics::Shader>::Load("shaders/transparency/clearing.shd");

	system.Context().DisableDepthTest();
	system.Context().DisableDepthWrite();

	clearer.Get().Bind();

	clearer.Get()["ABufferIndex"] = PageIndices;
	clearer.Get()["ABufferCounts"] = FragCount;
	clearer.Get()["ABufferSemaphore"] = Semaphore;

	clearer.Get()["ScreenSize"] = Math::Vector2ui(system.Context().GetTarget().GetWidth(), system.Context().GetTarget().GetHeight());
	Quad.PushGeometry(system.Context());

	clearer.Get().UnBind();

	system.Context().EnableDepthTest();
	system.Context().EnableDepthWrite();

	AtomicPageCounter.Write({ 1 });

}

void ABuffer::CheckPageSizes(RenderSystem &system)
{
	system.Context().AtomicCounterMemoryBarrier();

	std::vector<unsigned int> p;
	AtomicPageCounter.Read(p);
	

	int ExtraFrags = std::max(int(p[0]) - int(PageCount), 0);

	

	if (ExtraFrags > 0)
	{
		PageCount += (ExtraFrags/(PageSize/2) + 1) * 2;
		DepthPageBuffer.Build(PageCount * PageSize);
		ColorPageBuffer.Build(PageCount * PageSize);
		ModePageBuffer.Build(PageCount * PageSize);
		PageLinkBuffer.Build(PageCount);

		std::cout << "======================================" << std::endl;
		std::cout << "Pages used: " << p[0] << "/" << PageCount << std::endl;
		std::cout << "Extra Fragments: " << ExtraFrags << std::endl;
		std::cout << "Paging Size: " << (DepthPageBuffer.SizeInBytes() + ColorPageBuffer.SizeInBytes() + ModePageBuffer.SizeInBytes() + PageLinkBuffer.SizeInBytes()) << " Bytes." << std::endl;
	}
}

}}
