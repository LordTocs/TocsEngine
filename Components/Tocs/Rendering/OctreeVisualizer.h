#pragma once
#include "RenderObject.h"
#include "DynamicOctree.h"
#include "StaticGeometry.h"

namespace Tocs {
namespace Rendering {

template <class T>
class JobOctreeVisualizer  : public RenderObject
{
	JobOctree<T> &JobTree;
	class OctreeGeometry : public Geometry
	{
		Graphics::UniformMap Uniforms;
		const StaticGeometryType &Type;
		JobOctree<T> &JobTree;
	public:
		StaticGeometry(const Mesh &mesh, const StaticGeometryType &type)
			: MeshBuffer(&mesh),
			  Type(type) //Add type deduction from VertexFormat.
		{}

		const GeometryType &GetType () const { return Type; }

		Graphics::UniformMap::UniformValue &operator[] (const std::string &name)
		{ return Uniforms[name]; }

		void PassToShader (Graphics::Shader &shader) const
		{ Uniforms.PassToShader(shader); }

		int PartCount () const 
		{ return 1; }

		void PushGeometry (unsigned int part) const
		{ 
			
		}

		void Prep (const Camera &cam) const {}
	};
public:
	OctreeVisualizer(RenderSystem &system, JobOctree<T> &jobtree)
		: RenderObject (system), JobTree(jobtree)
	{}

protected:
	void QueueJobs ()
	{
	}
	void DequeueJobs ()
	{
	}

};

}}