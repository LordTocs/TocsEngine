#pragma once
#include <list>
#include "Camera.h"
#include "Job.h"
#include "Pipe.h"
#include "Geometry.h"
#include "Shading.h"
#include "ShaderPool.h"
namespace Tocs {
namespace Rendering {
class Job
{
	//List is shitty because of cache miss.
	std::list<Job*>::iterator ListIterator;
	Pipe *Pipe;
	const Geometry &Geom;
	int GeometryIndex;
	const Shading &Shad;
	Graphics::Shader &BuiltShader;
	
public:
	friend class Pipe;

	Job(const Geometry &geometry, const Shading &shading)
	  : Pipe(nullptr),
	    Geom(geometry),
		Shad(shading),
		BuiltShader(ShaderPool::Global.GetShader(geometry,shading)),
		GeometryIndex(0)
	{}
	
	~Job()
	{ Pipe->RemoveJob (*this); }

	void Render (Graphics::GraphicsContext &context, const Camera &cam);
};

}}