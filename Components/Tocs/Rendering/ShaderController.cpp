#include "ShaderController.h"
#include "RenderSystem.h"
namespace Tocs {
namespace Rendering {

ShaderController::ShaderController()
: t(0)
{

}
ShaderController::ShaderController(ShaderController &&moveme)
: UpdateShader(std::move(moveme.UpdateShader)), t(moveme.t)
{

}

void ShaderController::Update(float dt, ParticleDataBuffer &data, RenderSystem &system)
{
	t += dt;
	if (data.ActiveParticles != 0)
	{
		UpdateShader.Get().Bind();
		UpdateShader.Get()["t"] = t;
		UpdateShader.Get()["dt"] = dt;
		UpdateShader.Get()["ActiveParticles"] = data.ActiveParticles;
		data.Data.BindTo(Graphics::BufferTarget::ShaderStorage, 0);
		system.Context().Compute((data.ActiveParticles + 127) / 128);
		UpdateShader.Get().UnBind();
	}

}

ParticleController *ShaderController::Clone() const
{
	return new ShaderController(*this);
}

ShaderController ShaderController::Parse(const ParticleDescription& desc, Lexing::Tokenizer &tokens)
{
	static const std::string controllertemplate = Lexing::StringSource::FromFile("shaders/particles/shadercontroller.template").GetString();

	std::string updatesource;

	while (!tokens.EndOfStream())
	{
		if (tokens.PeekType() == Lexing::TokenType::Comment)
		{
			tokens.GetToken();
			continue;
		}

		if (tokens.Is("update"))
		{
			updatesource = tokens.GetTextIn("{", "}");
		}
	}
	std::string source = controllertemplate;
	static const std::string particle_struct_tag = "<%particlestruct%>";
	unsigned int pos = source.find(particle_struct_tag);

	source.replace(pos, particle_struct_tag.length(), desc.GetGLSLStruct());

	static const std::string update_tag = "<%updatesource%>";
	pos = source.find(update_tag);

	source.replace(pos, update_tag.length(), updatesource);

	Graphics::ShaderCode code(Graphics::ShaderType::Compute);
	code.Compile(source);
	if (!code.Compiled())
	{
		std::cout << "Error compiling shader controller update shader." << std::endl;
		std::cout << "==============================" << std::endl;
		std::cout << code.GetCompileErrors() << std::endl;
	}

	Graphics::Shader updateshader;
	updateshader.AddCode(code);
	updateshader.Link();
	updateshader.PrintDebugInformation();

	if (!updateshader.Linked())
	{
		std::cout << "Error linking shader controller update shader." << std::endl;
		std::cout << "==============================" << std::endl;
		std::cout << updateshader.GetLinkErrors() << std::endl;
	}

	ShaderController result;
	result.UpdateShader = Asset<Graphics::Shader>::Own(std::move(updateshader));

	return std::move(result);
	
}

}}