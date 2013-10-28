#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/Shader.h>
#include "Geometry.h"
#include "Pipeline.h"
#include "ShaderPool.h"

namespace Tocs {
namespace Rendering {

class Compositor
{
public:
	virtual ~Compositor() {}

	virtual void LinkShaderCode (Graphics::Shader &shader) const = 0;

	virtual void EmitCompositingJob (Geometry &geometry, Pipeline &pipeline) const = 0;
};

class FrameBufferCompositor : public Compositor
{
	Asset<Graphics::ShaderCode> CompositingShader;
public:
	FrameBufferCompositor ();

	void LinkShaderCode (ShaderConstruction &construction) const
	{ construction.AddCode(CompositingShader.Get()); }

};


}}