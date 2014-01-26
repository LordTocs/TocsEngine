#include "ParticleGeometry.h"
#include <Tocs/Graphics/VertexFormat.h>
#include <Tocs/Core/Tokenizer.h>
#include <sstream>
namespace Tocs {
namespace Rendering {

ParticleGeometry::ParticleGeometry(const ParticleDescription &description, unsigned int particlecount)
: ParticleData(description,particlecount)
{
	Graphics::VertexFormat particledataformat;
	for (auto &v : description.Variables)
	{
		particledataformat.AddMember(v.Name(), v.Type(), false, true);
	}

	VertexArray.Bind();
	VertexArray.AddIBO(QuadIndexBuffer.Get());
	VertexArray.AddVBO(QuadVertexBuffer.Get(),PositionTexture::Format.Get());
	VertexArray.AddVBO(ParticleData.Data, particledataformat);
	VertexArray.UnBind();
}

DrawCall ParticleGeometry::GetCall() const
{
	return DrawCall(VertexArray, 0, 2, &ParticleData.ActiveParticles);
}


Graphics::Buffer<PositionTexture> ParticleGeometry::CreateVertQuadBuffer()
{
	PositionTexture verts[] = { PositionTexture(Math::Vector3(-0.5, 0.5, 0), Math::Vector2(0, 0)),
								PositionTexture(Math::Vector3(0.5, 0.5, 0), Math::Vector2(1, 0)),
								PositionTexture(Math::Vector3(-0.5, -0.5, 0), Math::Vector2(0, 1)),
								PositionTexture(Math::Vector3(0.5, -0.5, 0), Math::Vector2(1, 1)), };

	Graphics::Buffer<PositionTexture> result(4);
	result.Write(verts, 4);
	return std::move(result);
}
FirstUseStatic<Graphics::Buffer<PositionTexture>, ParticleGeometry::CreateVertQuadBuffer> ParticleGeometry::QuadVertexBuffer;

Graphics::Buffer<unsigned short> ParticleGeometry::CreateQuadIndexBuffer()
{
	unsigned short inds[] = { 0, 1, 2, 1, 2, 3 };
	Graphics::Buffer<unsigned short> result(6);
	result.Write(inds, 6);
	return std::move(result);
}

FirstUseStatic<Graphics::Buffer<unsigned short>, ParticleGeometry::CreateQuadIndexBuffer> ParticleGeometry::QuadIndexBuffer;


static std::string GetVertexShader(const ParticleDescription &description)
{
	static std::string vertextemplate = Lexing::StringSource::FromFile("particles/vertex.template").GetString();

	std::stringstream inputs;

	for (const auto &v : description.Variables)
	{
		inputs << "in " << v.Type().ToShaderVariable().ToGLSLTypeString() << " In" << v.Name() << ";" << std::endl;
		inputs << "out " << v.Type().ToShaderVariable().ToGLSLTypeString() << " " << v.Name() << ";" << std::endl;
	}

	std::stringstream passthrough;
	for (const auto &v : description.Variables)
	{
		passthrough << v.Name() << " = In" << v.Name() << ";" << std::endl;
	}

	std::string result = vertextemplate;

	static std::string inputkey = "<%inputs%>";
	auto varloc = result.find(inputkey);
	if (varloc != std::string::npos)
	{
		result.replace(varloc, inputkey.length(), inputs.str());
	}

	static std::string passkey = "<%passthrough%>";
	auto passloc = result.find(passkey);
	if (passloc != std::string::npos)
	{
		result.replace(passloc, passkey.length(), passthrough.str());
	}

	return result;
}

void ParticleGeometry::LinkShaders(ShaderConstruction &construction, bool HasVertexComponent) const
{
	Graphics::ShaderCode vertex(Graphics::ShaderType::Vertex);
	vertex.Compile(GetVertexShader(ParticleData.GetDescription()));
}

void ParticleGeometry::AddShaderInputs(Graphics::ShaderInput &input) const
{

}


}}
