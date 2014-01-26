#include "ParticleSystem.h"
#include <sstream>
#include <Tocs/Core/Tokenizer.h>

using namespace Tocs::Lexing;
namespace Tocs {
namespace Rendering {
	/*

ParticleSystemSource ParticleSystemSource::LoadFromFile(const std::string &filename)
{
	ParticleSystemSource result;

	Lexing::StringSource source = Lexing::StringSource::FromFile(filename);

	Lexing::Tokenizer tokens(source);

	std::string updatesource;

	while (!tokens.EndOfStream())
	{
		auto cmd = tokens.GetTokenData();
		if (cmd == TokenType::Word)
		{
			if (cmd == "update")
			{
				updatesource = tokens.GetTextIn("{", "}");
			}
			else if (cmd == "var")
			{
				if (!tokens.Is(":")) {}

				Graphics::ShaderVariableType type = Graphics::ShaderVariableType::FromGLSLTypeString(tokens.GetToken());
				std::string name = tokens.GetToken();
				result.AddVariable(name, type);
			}
			else if (cmd == "material")
			{
				result.ParticleMaterial = std::move(MaterialSource::LoadFromConfig(tokens.GetTextIn("{", "}")));
			}
		}
	}

	return std::move(result);
}

*/

void ParticleSystem::Update(float dt)
{
	//Emit new ones
	Emitter->Update(dt, Particles.Data());

	//Update all the particles
	Controller->Update(dt, Particles.Data());

	//Collate active particles to the front of the buffer.
	Particles.Data().Organize();
}

}
}
