#pragma once
#include <Tocs/Graphics/Shader.h>
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

	virtual const GeometryType &GetType () const = 0;
	virtual void PassToShader (Graphics::Shader &shader) const = 0;
	virtual void PushGeometry (unsigned int part) const = 0;
	virtual int PartCount () const = 0;
};
 
}}

