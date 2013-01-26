#pragma once
#include "Material.h"
#include "Pipeline.h"
//#include "PermutationValueSet.h"
//#include "Permutation.h"
#include "ShaderPermutator.h"
namespace Tocs {
namespace Rendering {

class DeferredMaterial : public MaterialPass
{
	Asset<ShaderPermutator> DeferredTemplate;

	Permutations::PermutationValueSet Values;
	Permutation &ConstructedShader;

public:
	DeferredMaterial(const std::string &config);
	~DeferredMaterial();

	Graphics::ShaderCode &GetCompiledShader ();
	void ApplyUniforms (Graphics::Shader &shader);

	Pipe &GetPipe (Pipeline &pipeline);
	
};

}}