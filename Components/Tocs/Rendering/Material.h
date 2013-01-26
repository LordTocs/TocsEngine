#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Pipe.h"
#include "GeometryHandler.h"
#include "MaterialPassSession.h"



namespace Tocs {
namespace Rendering {

class MaterialPass
{

public:
	MaterialPass () {}

	virtual Pipe &GetPipe (Pipeline &pipeline) = 0;
	virtual ~MaterialPass () {}
	virtual Graphics::ShaderCode &GetCompiledShader () = 0;
	virtual void ApplyUniforms (Graphics::Shader &shader) = 0;
};

class Material
{
	std::vector<std::unique_ptr<MaterialPass>> Passes;
public:
	Material () {}
	Material (const Material &copyme);
	Material (Material &&moveme);

	std::vector<std::unique_ptr<MaterialPass>>::iterator BeginPasses ()
	{ return Passes.begin (); }

	std::vector<std::unique_ptr<MaterialPass>>::iterator EndPasses ()
	{ return Passes.end (); }

	MaterialPass &GetPass (unsigned int index) { return *Passes[index]; }
	const MaterialPass &GetPass(unsigned int index) const { return *Passes[index]; }

	static Material LoadFromFile (const std::string &filename);
};

}}