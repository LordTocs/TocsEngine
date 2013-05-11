#pragma once
#include "Job.h"
#include "RenderObject.h"
#include "StaticGeometry.h"
#include "BasicShading.h"
#include "LightHulls.h"
#include <Tocs/Math/Color.h>
namespace Tocs {
namespace Rendering {

class PointLight;

class LightCubeGeometry : public Geometry
{
	Graphics::UniformMap Uniforms;
	const StaticGeometryType &Type;
	const Mesh *MeshBuffer;
	const Mesh *InverseMeshBuffer;
	bool Invert;
	PointLight *Light;
public:
	LightCubeGeometry(PointLight *light)
		: MeshBuffer(&LightHulls::Cube.Get()),
		  InverseMeshBuffer(&LightHulls::InverseCube.Get()),
		  Type(LightHulls::GeometryType.Get()),
		  Light(light),
		  Invert(false)
	{}

	const GeometryType &GetType () const { return Type; }

	Graphics::UniformMap::UniformValue &operator[] (const std::string &name)
	{ return Uniforms[name]; }

	void PassToShader (Graphics::Shader &shader) const
	{ Uniforms.PassToShader(shader); }

	int PartCount () const 
	{ return MeshBuffer->PartCount(); }

	void PushGeometry (unsigned int part) const;
	

	void Prep (const Camera &cam) const;
};

class PointLight : public RenderObject
{
	LightCubeGeometry LightGeometry;
	Asset<BasicShadingType> LightShadingType;
	BasicShading LightShading;
	Job DeferredJob;
protected:
	void QueueJobs ();
	void DequeueJobs ();
public:
	Math::Color Color;
	float Intensity;
	float Radius;
	PointLight(RenderSystem &system);
	void Update(float dt);
};

}}