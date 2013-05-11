#pragma once
#include <Tocs/Graphics/Shader.h>
#include "Camera.h"
namespace Tocs {
namespace Rendering {

class GeometryType
{
public:
	virtual ~GeometryType () {}

	virtual void AddShaders (Graphics::Shader &targetshader) const = 0;
};

class Geometry
{
public:
	virtual ~Geometry () {}

	virtual void Prep (const Camera &cam) const = 0;
	virtual const GeometryType &GetType () const = 0;
	virtual void PassToShader (Graphics::Shader &shader) const = 0;
	virtual void PushGeometry (unsigned int part) const = 0;
	virtual int PartCount () const = 0;
};
 
}}

