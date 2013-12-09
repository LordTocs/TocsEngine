#pragma once
#include <vector>
#include <memory>
#include <Tocs/Math/Vector.h>
#include <Tocs/Core/MemberChecks.h>
#include <Tocs/Rendering/Mesh.h>

namespace Tocs {
namespace MeshTools {

//Ugly Macro Fun Time! Oh God Why?
//GEN_MEMBER_CHECKER (Position)
//GEN_MEMBER_CHECKER (TextureCoordinate)
//GEN_MEMBER_CHECKER (Normal)
	
template<class V, class I>
class MeshBuilder;

template<class V, class I>
class Face;

template <class V, class I = unsigned short>
class Vertex
{
	I Index;
	MeshBuilder<V,I> &Builder;

	Vertex(I index, MeshBuilder<V,I> &builder)
		: Index(index), Builder(builder) {}

public:
	friend class MeshBuilder<V,I>;
	friend class Face<V,I>;

	V &Get () { return Builder.Vertices[Index]; }
	const V&Get () const { return Builder.Vertices[index]; }
};

template <class V, class I = unsigned short>
class Face
{
	unsigned int IndexIndex;

	MeshBuilder<V,I> &Builder;

	Face(unsigned int ii, MeshBuilder<V,I> &builder)
		: IndexIndex(ii), Builder(builder) {}
public:
	friend class MeshBuilder<V,I>;

	Math::Vector3 GetNormal () const
	{
		Math::Vector3 a = V2().Get().Position - V1().Get().Position;
		Math::Vector3 b = V3().Get().Position - V1().Get().Position;
		return a.Cross (b);
	}

	void FacePoint (const Math::Vector3 &point)	
	{
		Math::Vector3 compare = point - V1().Get().Position;
		float dot = compare.Dot (GetNormal ());
		if (dot < 0)
			FlipOrder ();
	}

	void FaceAwayFromPoint (const Math::Vector3 &point)	
	{
		Math::Vector3 compare = V1().Get().Position - point;
		float dot = compare.Dot (GetNormal ());
		if (dot < 0)
			FlipOrder ();
	}

	void FaceNormal (const Math::Vector3 &normal)
	{
		if (normal.Dot (GetNormal ()) < 0)
		{
			FlipOrder ();
		}
	}
	void FlipOrder ()
	{
		I temp = Builder.Indices[IndexIndex];
		Builder.Indices[IndexIndex] = Builder.Indices[IndexIndex+2];
		Builder.Indices[IndexIndex+2] = temp;
	}

	Vertex<V,I> V1 () { return Vertex<V,I> (Builder.Indices[IndexIndex],Builder); }
	Vertex<V,I> V2 () { return Vertex<V,I> (Builder.Indices[IndexIndex+1],Builder); }
	Vertex<V,I> V3 () { return Vertex<V,I> (Builder.Indices[IndexIndex+2],Builder); }
	Vertex<V,I> V1 () const { return Vertex<V,I> (Builder.Indices[IndexIndex],Builder); }
	Vertex<V,I> V2 () const { return Vertex<V,I> (Builder.Indices[IndexIndex+1],Builder); }
	Vertex<V,I> V3 () const { return Vertex<V,I> (Builder.Indices[IndexIndex+2],Builder); }
};

template <class V, class I = unsigned short>
class MeshBuilder
{
	std::vector<V> Vertices;
	std::vector<I> Indices;
public:
	friend class Vertex<V,I>;
	friend class Face<V,I>;
	Vertex<V,I> GetVertex ()
	{
		Vertices.push_back (V ());
		return Vertex<V,I> (static_cast<I>(Vertices.size () - 1),*this);
	}
	Face<V,I> CreateFace (const Vertex<V,I> &v1, const Vertex<V,I> &v2, const Vertex<V,I> &v3)
	{
		unsigned int ii = Indices.size ();
		Indices.push_back(v1.Index);
		Indices.push_back(v2.Index);
		Indices.push_back(v3.Index);
		return Face<V,I> (ii,*this);

	}
	
	std::pair<Face<V,I>,Face<V,I>> CreateQuad (const Vertex<V,I> &v1, const Vertex<V,I> &v2, const Vertex<V,I> &v3, const Vertex<V,I> &v4)
	{
		return std::make_pair (CreateFace (v1,v2,v3), CreateFace (v1,v3,v4));
	}

	void ComputeNormals ()
	{
		for (int i = 0; i < Indices.size(); i += 3)
		{
			Face<V,I> f (i,*this);
			Math::Vector3 normal = f.GetNormal ();
			f.V1().Get().Normal += normal;
			f.V2().Get().Normal += normal;
			f.V3().Get().Normal += normal;
		}

		for (int vert = 0; vert < Vertices.size (); ++vert)
		{
			Vertices[vert].Normal.Normalize ();
		}
	}
	
	Rendering::Mesh CreateMesh ()
	{
		Rendering::Mesh result (Vertices.size (), Indices.size (),V::Format.Get(),Graphics::IndexFormat::FromType<I>());

		result.WriteVertices (&Vertices[0], Vertices.size ());
		result.WriteIndices  (&Indices[0], Indices.size ());
		result.AddPart(Rendering::MeshPart (0,Indices.size()/3));

		return result;
	}
};

}}