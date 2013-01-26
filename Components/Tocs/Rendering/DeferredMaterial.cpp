#include "DeferredMaterial.h"
#include "ShaderPool.h"
#include <iostream>
#include <Tocs/Core/Tokenizer.h>
#include <Tocs/Math/Color.h>
#include <Tocs/Core/Float.h>

using namespace std;
using namespace Tocs::Lexing;
using namespace Tocs::Graphics;
using namespace Tocs::Math;
using namespace Tocs::Rendering::Permutations;

namespace Tocs {
namespace Rendering {

DeferredMaterial::DeferredMaterial(const std::string &config)
	: DeferredTemplate(Asset<ShaderPermutator>::Load ("DeferredTemplate.tgl")),
	  Values(config),
	  ConstructedShader(DeferredTemplate.Get().GetPermutation (Values))
{
}


DeferredMaterial::~DeferredMaterial(void)
{
}


Graphics::ShaderCode &DeferredMaterial::GetCompiledShader ()
{
	return ConstructedShader.GetCode ();
}
void DeferredMaterial::ApplyUniforms (Graphics::Shader &shader)
{
	ConstructedShader.Apply (Values,shader);
}

Pipe &DeferredMaterial::GetPipe (Pipeline &pipeline)
{
	return pipeline.Deferred;
}

}}