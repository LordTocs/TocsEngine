#pragma once
#include "DrawCall.h"
#include <Tocs/Graphics/Shader.h>
#include <Tocs/Graphics/ShaderState.h>
#include "ShaderPool.h"

namespace Tocs {
namespace Rendering {

class Geometry
{
public:
	Geometry(){}

	virtual DrawCall GetCall () const = 0;

	virtual void LinkShaders (ShaderConstruction &construction, bool HasVertexComponent) const = 0;

	virtual void AddShaderInputs(Graphics::ShaderStateSet &input) const = 0;
};

}}
