#include "ParticleSystem.h"
#include <sstream>
#include <Tocs/Core/Tokenizer.h>
#include <Tocs/Core/Integer.h>
#include "PointEmitter.h"
#include "ShaderController.h"

using namespace Tocs::Lexing;
namespace Tocs {
namespace Rendering {

ParticleSystemSource::ParticleSystemSource(ParticleSystemSource &&moveme)
: Description(std::move(moveme.Description))
, ParticleMaterial(std::move(moveme.ParticleMaterial))
, Emitter(std::move(moveme.Emitter))
, Controller(std::move(moveme.Controller))
, MaxParticles(moveme.MaxParticles)
{

}


std::string StripQuotes(std::string string)
{
	//scott is a cool kid
	return string.substr(1, string.length() - 2);
}

ParticleSystemSource ParticleSystemSource::LoadFromFile(const std::string &filename)
{
	ParticleSystemSource result;

	Lexing::StringSource source = Lexing::StringSource::FromFile(filename);

	Lexing::Tokenizer tokens(source);

	while (!tokens.EndOfStream())
	{
		auto cmd = tokens.GetTokenData();
		if (cmd == TokenType::Word)
		{
			if (cmd == "shader_controller")
			{
				std::string controller = tokens.GetTextIn("{", "}");
				StringSource controllersource(controller);
				Tokenizer tokens(controllersource);
				result.Controller.reset(new ShaderController(ShaderController::Parse(result.Description, tokens)));
			}
			else if (cmd == "point_emitter")
			{
				std::string emit = tokens.GetTextIn("{", "}");
				StringSource emitsource(emit);
				Tokenizer tokens(emitsource);
				result.Emitter.reset (new PointEmitter(PointEmitter::Parse(result.Description,tokens)));
			}
			else if (cmd == "description")
			{
				std::string desc = tokens.GetTextIn("{", "}");
				StringSource descsource(desc);
				Tokenizer tokens(descsource);
				result.Description = ParticleDescription::Parse(tokens);
			}
			else if (cmd == "material")
			{
				if (tokens.Is(":"))
				{
					if (tokens.PeekType() != TokenType::StringLiteral)
					{}

					std::string file = StripQuotes(tokens.GetToken());
					result.ParticleMaterial = Asset<MaterialSource>::Load(file);
				}
				else
				{
					std::string material = tokens.GetTextIn("{", "}");
					result.ParticleMaterial = Asset<MaterialSource>::Own(MaterialSource::LoadFromConfig(material));

				}
			}
			else if (cmd == "particle_count")
			{
				if (!tokens.Is(":"))
				{
					//ERRORS
				}

				result.MaxParticles = Integer::ParseU32(tokens.GetToken());
			}
		}
	}

	return std::move(result);
}

ParticleSystem::ParticleSystem(RenderSystem &system, const Asset<ParticleSystemSource> &source)
: Source(source)
, Controller(source.Get().GetController())
, Emitter(source.Get().GetEmitter())
, Particles(source.Get().GetDescription(), source.Get().GetMaxParticles())
, ParticleMaterial(source.Get().GetMaterialSource())
, Drawable(system)
{

}
ParticleSystem::ParticleSystem(ParticleSystem &&moveme)
: Source(std::move(moveme.Source))
, Controller(std::move(moveme.Controller))
, Emitter(std::move(moveme.Emitter))
, Particles(std::move(moveme.Particles))
, ParticleMaterial(std::move(moveme.ParticleMaterial))
, Drawable(std::move(static_cast<Drawable&>(*this)))
{
	
}

void ParticleSystem::Update(float dt)
{
	//Emit new ones
	Emitter->Update(dt, Particles.Data());

	//Update all the particles
	Controller->Update(dt, Particles.Data(),System);

	//Collate active particles to the front of the buffer.
	Particles.Data().Organize();
}

void ParticleSystem::QueueJobs()
{
	ParticleMaterial.QueueJob(Particles, System);
}
void ParticleSystem::DeQueueJobs()
{
	ParticleMaterial.DeQueueJob();
}

}
}
