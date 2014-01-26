#include "SMAA.h"
#include <smaa_glsl.h>
#include <smaa_searchtex.h>
#include <smaa_areatex.h>
#include "RenderSystem.h"

namespace Tocs {
namespace Rendering {

static void ShaderCodeErrorCheck(Graphics::ShaderCode &code, std::string name)
{
	if (!code.Compiled())
	{
		std::cout << std::endl;
		std::cout << name << " - Compile Errors" << std::endl;
		std::cout << "=====================================" << std::endl;
		std::cout << code.GetCompileErrors() << std::endl;
		std::cout << std::endl;
	}
}


static void ShaderErrorCheck(Graphics::Shader &shader, std::string name)
{
	if (!shader.Linked())
	{
		std::cout << std::endl;
		std::cout << name << " - Link Errors" << std::endl;
		std::cout << "=====================================" << std::endl;
		std::cout << shader.GetLinkErrors() << std::endl;
		std::cout << std::endl;
	}
}

/*void SMAA::BuildShaders()
{
	//EDGE

	Graphics::ShaderCode edgevs(Graphics::ShaderType::Vertex);
	edgevs.Compile(edge_vs);
	ShaderCodeErrorCheck(edgevs, "SMAA Edge VS");


	Graphics::ShaderCode edgeps(Graphics::ShaderType::Pixel);
	edgeps.Compile(edge_ps);
	ShaderCodeErrorCheck(edgeps, "SMAA Edge PS");

	EdgeShader.AddCode(edgevs);
	EdgeShader.AddCode(edgeps);
	EdgeShader.Link();
	ShaderErrorCheck(EdgeShader, "SMAA Edge Shader");


	/////BLEND

	Graphics::ShaderCode blendvs(Graphics::ShaderType::Vertex);
	blendvs.Compile(blend_vs);
	ShaderCodeErrorCheck(blendvs, "SMAA Blend VS");


	Graphics::ShaderCode blendps(Graphics::ShaderType::Pixel);
	blendps.Compile(blend_ps);
	ShaderCodeErrorCheck(blendps, "SMAA Blend PS");

	BlendShader.AddCode(edgevs);
	BlendShader.AddCode(edgeps);
	BlendShader.Link();
	ShaderErrorCheck(BlendShader, "SMAA Blend Shader");

	/////NEIGHBORHOOD

	Graphics::ShaderCode neighborhoodvs(Graphics::ShaderType::Vertex);
	neighborhoodvs.Compile(neighborhood_vs);
	ShaderCodeErrorCheck(neighborhoodvs, "SMAA Neighborhood VS");


	Graphics::ShaderCode neighborhoodps(Graphics::ShaderType::Pixel);
	neighborhoodps.Compile(neighborhood_ps);
	ShaderCodeErrorCheck(neighborhoodps, "SMAA Neighborhood PS");

	NeighborhoodShader.AddCode(neighborhoodvs);
	NeighborhoodShader.AddCode(neighborhoodps);
	NeighborhoodShader.Link();
	ShaderErrorCheck(NeighborhoodShader, "SMAA Neighborhood Shader");
}*/

void SMAA::SetupRenderTargets()
{
	EdgeTarget.SetTexture(EdgeTex, 0);

	BlendTarget.SetTexture(BlendTex, 0);
}

void SMAA::SetupReferenceTextures()
{
	AreaTex.SetData(Graphics::TextureDataFormat::RG8, areaTexBytes);
	//AreaTex.LoadRaw(Graphics::TextureDataFormat::RG8, "smaa/smaa_area.raw");
	//AreaTex.SaveDebug("Area.png");
	SearchTex.SetData(Graphics::TextureDataFormat::R8, searchTexBytes);
	//SearchTex.LoadRaw(Graphics::TextureDataFormat::R8, "smaa/smaa_search.raw");
	//SearchTex.SaveDebug("Search.png");
}

SMAA::SMAA(RenderSystem &system)
: EdgeTex(system.Context().GetTarget().GetWidth(), system.Context().GetTarget().GetHeight(), Graphics::TextureFiltering::None, Graphics::TextureFormat::RGBA8)
, BlendTex(system.Context().GetTarget().GetWidth(), system.Context().GetTarget().GetHeight(), Graphics::TextureFiltering::None, Graphics::TextureFormat::RGBA8)
, AreaTex(AREATEX_WIDTH, AREATEX_HEIGHT, Graphics::TextureFiltering::None, Graphics::TextureFormat::RG8)
, SearchTex(SEARCHTEX_WIDTH, SEARCHTEX_HEIGHT, Graphics::TextureFiltering::None, Graphics::TextureFormat::R8)
, System(&system)
, BlendShader(Asset<Graphics::Shader>::Load("smaa/blend.shd"))
, EdgeShader(Asset<Graphics::Shader>::Load("smaa/edge.shd"))
, NeighborhoodShader(Asset<Graphics::Shader>::Load("smaa/neighborhood.shd"))
{
	std::cout << "Edge: " << EdgeTex.GetID() << " Blend: " << BlendTex.GetID() << std::endl;

	SetupReferenceTextures();
	//BuildShaders();
	SetupRenderTargets();
}

void SMAA::EdgeDetectionPass(const Graphics::Texture2D &albedo)
{
	//albedo.SaveDebug("Albedo.png");

	EdgeTarget.Bind();
	System->Context().ClearColor(Math::Color(0,0,0,0));
	EdgeShader.Get().Bind();

	EdgeShader.Get()["InvScreenSize"] = Math::Vector2(1.0f / System->Context().GetTarget().GetWidth(), 1.0f / System->Context().GetTarget().GetHeight());
	EdgeShader.Get()["albedo_tex"] = albedo;

	Quad.PushGeometry(System->Context());

	EdgeShader.Get().UnBind();
	EdgeTarget.UnBind();

	//EdgeTex.SaveDebug("Edges.png");
}
void SMAA::BlendingWeightPass()
{
	BlendTarget.Bind();
	System->Context().ClearColor(Math::Color(0, 0, 0, 0));
	BlendShader.Get().Bind();

	BlendShader.Get()["InvScreenSize"] = Math::Vector2(1.0f / System->Context().GetTarget().GetWidth(), 1.0f / System->Context().GetTarget().GetHeight());
	BlendShader.Get()["edge_tex"] = EdgeTex;
	BlendShader.Get()["area_tex"] = AreaTex;
	BlendShader.Get()["search_tex"] = SearchTex;

	Quad.PushGeometry(System->Context());

	BlendShader.Get().UnBind();
	BlendTarget.UnBind();

	//BlendTex.SaveDebug("Blend.png");
}
void SMAA::FinalBlendingPass(const Graphics::Texture2D &albedo)
{
	NeighborhoodShader.Get().Bind();

	NeighborhoodShader.Get()["InvScreenSize"] = Math::Vector2(1.0f / System->Context().GetTarget().GetWidth(), 1.0f / System->Context().GetTarget().GetHeight());
	NeighborhoodShader.Get()["albedo_tex"] = albedo;
	NeighborhoodShader.Get()["blend_tex"] = BlendTex;

	Quad.PushGeometry(System->Context());

	NeighborhoodShader.Get().UnBind();
}

}}