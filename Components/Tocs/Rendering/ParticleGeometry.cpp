#include "ParticleGeometry.h"
#include <Tocs/Graphics/VertexFormat.h>
#include <Tocs/Core/Tokenizer.h>
#include <sstream>
namespace Tocs {
namespace Rendering {


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


ParticleGeometry::ParticleGeometry(const ParticleDescription &description, unsigned int particlecount)
: ParticleData(description,particlecount)
, VertexShader(Graphics::ShaderType::Vertex)
{
	Graphics::VertexFormat particledataformat(2);
	for (auto &v : description.Variables)
	{
		particledataformat.AddMember(v.Name(), v.Type(), false, true);
	}

	VertexArray.Bind();
	VertexArray.AddIBO(QuadIndexBuffer.Get());
	VertexArray.AddVBO(QuadVertexBuffer.Get(),PositionTexture::Format.Get());
	VertexArray.AddStd140VBO(ParticleData.Data, particledataformat);
	VertexArray.UnBind();

	VertexShader.Compile(GetVertexShader(ParticleData.GetDescription()));
	if (!VertexShader.Compiled())
	{
		std::cout << "Errors Compiling Particle Vertex Shader" << std::endl;
		std::cout << "===========================" << std::endl;
		std::cout << VertexShader.GetCompileErrors() << std::endl;
	}
}

ParticleGeometry::ParticleGeometry(ParticleGeometry &&moveme)
: ParticleData(std::move(moveme.ParticleData))
, VertexArray(std::move(moveme.VertexArray))
, VertexShader(std::move(moveme.VertexShader))
{

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
	unsigned short inds[] = { 2, 1, 0, 1, 2, 3 };
	Graphics::Buffer<unsigned short> result(6);
	result.Write(inds, 6);
	return std::move(result);
}

FirstUseStatic<Graphics::Buffer<unsigned short>, ParticleGeometry::CreateQuadIndexBuffer> ParticleGeometry::QuadIndexBuffer;




void ParticleGeometry::LinkShaders(ShaderConstruction &construction, bool HasVertexComponent) const
{
	construction.AddCode(VertexShader);
}

void ParticleGeometry::AddShaderInputs(Graphics::ShaderInput &input) const
{

}


}}
