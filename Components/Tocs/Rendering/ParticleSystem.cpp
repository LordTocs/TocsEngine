#include "ParticleSystem.h"
#include <sstream>
#include <Tocs/Core/Tokenizer.h>

using namespace Tocs::Lexing;
namespace Tocs {
namespace Rendering {
	/*
ParticleSystemSource::ParticleSystemSource()
: GeneratedUpdateCode(Graphics::ShaderType::Compute)
, GeneratedVertexCode(Graphics::ShaderType::Vertex)
, MaxParticleCount(100)
, ParticleByteSize(0)
{
	AddVariable("Position", Graphics::ShaderVariableType::Vector3);
	AddVariable("Size", Graphics::ShaderVariableType::Vector2);
	AddVariable("Rotation", Graphics::ShaderVariableType::Float);
	AddVariable("Life", Graphics::ShaderVariableType::Float);
}

void ParticleSystemSource::GenerateVertexShader()
{
	std::stringstream ss;

	ss <<
		"#version 400 \n\
		uniform mat4 Projection; \n\
		uniform mat4 View; \n\
		\n\
		in vec4 GeometryPosition; \n\
		in vec2 TextureCoordinate; \n";

	for (auto &v : Variables)
	{
		ss << "in " << v.Type().ToGLSLTypeString() << " In" << v.Name() << ";" << std::endl;
		ss << "out " << v.Type().ToGLSLTypeString() << " " << v.Name() << ";" << std::endl;
	}

	ss << "void main() \n\
		   {\n";

	for (auto &v : Variables)
	{
		ss << v.Name() << " = In" << v.Name() << ";" << std::endl;
	}

	ss << "\n\
		  	vec3 ParticlePosition = (View * vec4(Position, 1)).xyz;\n\
			vec3 Offset = vec3(GeometryPosition.xy * Size * vec2(cos(Rotation), sin(Rotation)), 0);\n\
			gl_Position = Projection * vec4(ParticlePosition + Offset, 1);\n\
		}\n";

	GeneratedVertexCode.Compile(ss.str());
}

void ParticleSystemSource::GenerateUpdateShader(const std::string &updatefunc)
{
	std::stringstream ss;

	ss << "#version 440\n\
			layout(local_size_x = 128, local_size_y = 1, local_size_z = 1) in;\n\
			struct Particle\n\
			{\n";
	for (auto &v : Variables)
	{
		ss <<  v.Type().ToGLSLTypeString() << " " << v.Name() << ";" << std::endl;
	}
	ss << "\
		  		uniform float dt;\n\
				uniform float t;\n\
				uniform unsigned int ActiveParticles;\n\
				\n\
				layout(std140, binding = 6) buffer ParticleBuffer\n\
				{\n\
				struct Particle Particles[];\n\
				};\n\
				\n\
				void main()\n\
				{\n\
					unsigned int index = gl_GlobalInvocationID;\n\
					Particles[index].Life -= dt;\n\
					if (index >= ActiveParticles)\n\
						return;\n";

	ss << updatefunc;
	ss << "}\n";

	GeneratedUpdateCode.Compile(ss.str());
}



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



std::mt19937 ParticleSystem::SetupRandom()
{
	std::mt19937 engine;
	std::random_device device;
	engine.seed(device());
	return std::move(engine);
}

ParticleSystem::ParticleSystem(RenderSystem &system, const Asset<ParticleSystemSource> &source)
: Drawable(system)
, Source(source)
, ParticleDataBuffer(source.Get().VariablesByteSize() * source.Get().ParticleCount())
, ActiveParticles(0)
, LifeDistribution(2,3)
, TotalLife(0)
{

}

//Swaps particles until all particles with life > 0 are at the beginning of the array.
//does NOT sort.
void ParticleSystem::CollateParticles()
{
	
	unsigned char *buffer = static_cast<unsigned char *> (ParticleDataBuffer.Map());
	unsigned char *frontptr = buffer;
	unsigned char *backptr = buffer + (Source.Get().ParticleCount() - 1) * Source.Get().VariablesByteSize();
	unsigned int size = Source.Get().VariablesByteSize();
	std::unique_ptr<unsigned char[]> tempbuffer(new unsigned char[size]);
	//Iterate to start positions

	while ((*reinterpret_cast<float*> (frontptr + 24)) > 0)
		frontptr += size;
	while ((*reinterpret_cast<float*> (backptr + 24))  < 0)
		backptr  -= size;

	while (frontptr < backptr)
	{
		if (((*reinterpret_cast<float*> (frontptr + 24)) < 0) && ((*reinterpret_cast<float*> (backptr + 24))  > 0))
		{
			//Swap the two particles in the buffer
			std::memcpy(tempbuffer.get(), frontptr, size);
			//back to front
			std::memcpy(frontptr, backptr, size);
			//temp to back
			std::memcpy(backptr, tempbuffer.get(), size);

			while ((*reinterpret_cast<float*> (frontptr + 24)) > 0)
				frontptr += size;
			while ((*reinterpret_cast<float*> (backptr + 24))  < 0)
				backptr -= size;
		}
	}

	ActiveParticles = (frontptr - buffer) / size;

	ParticleDataBuffer.UnMap();
}

void ParticleSystem::FormatNewParticle(unsigned char *dataptr)
{
	(*reinterpret_cast<Math::Vector3*> (dataptr)) = Transform.GetWorldPosition(); //Position
	(*reinterpret_cast<Math::Vector2*> (dataptr + 12))(0.1, 0.1); //Size
	(*reinterpret_cast<float*> (dataptr + 20)) = 0; //Rotation
	(*reinterpret_cast<float*> (dataptr + 24)) = LifeDistribution(Engine.Get()); //Life	
}


void ParticleSystem::EmitParticles(int n)
{
	unsigned char *buffer = static_cast<unsigned char *> (ParticleDataBuffer.Map());

	for (int i = ActiveParticles; i < Source.Get().ParticleCount(); ++i)
	{
		FormatNewParticle(buffer + i * Source.Get().VariablesByteSize());
	}

	ParticleDataBuffer.UnMap();
}

void ParticleSystem::Update(float dt)
{
	TotalLife += dt;
	//Update via shader
	Source.Get().ParticleShader().Bind();

	ParticleDataBuffer.BindTo(Graphics::BufferTarget::ShaderStorage, 0);

	System.Context().Compute((ActiveParticles + (Source.Get().GetWorkGroupSize() - 1)) / Source.Get().GetWorkGroupSize());

	Source.Get().ParticleShader().UnBind();

	CollateParticles();

	if (ActiveParticles < Source.Get().ParticleCount())
	{
		EmitParticles(Source.Get().ParticleCount() - ActiveParticles);
	}
}
*/
}
}
