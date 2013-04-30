#pragma once
#include <Tocs/Graphics/Shader.h>

namespace Tocs {
namespace Rendering {

class ShadingType
{
public:
	virtual ~ShadingType () {}

	virtual void AddShaders (Graphics::Shader &targetshader) const = 0;
};

class Shading
{
public:
	virtual ~Shading() {}
	virtual const ShadingType &GetType () const = 0;
	virtual void PassToShader (Graphics::Shader &shader) const = 0;
};

}}