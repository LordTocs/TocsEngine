#include "Chunk.h"
#include <Tocs/Math/Vector3i.h>
#include <Tocs/Math/Vector2i.h>
using namespace Tocs::Math;

namespace Tocs {
namespace Voxels {

Chunk::Chunk ()
	: Voxels()
{
	std::memset(&Voxels,0,sizeof(Voxel)*16*16*16);
}

void Chunk::GenerateMesh ()
{
	MeshTools::MeshBuilder<Rendering::PositionTextureNormal> builder;
	for (int x = 0; x < 16; ++x)
	{
		for (int y = 0; y < 16; ++y)
		{
			for (int z = 0; z < 16; ++z)
			{
				Voxelize (Math::Vector3i(x,y,z),builder);
			}
		}
	}
	builder.ComputeNormals();
	GeneratedMesh = std::unique_ptr<Rendering::Mesh> (new Rendering::Mesh(builder.CreateMesh ()));
}

static Math::Vector3i NeighborOffsets [6] = {Math::Vector3i(1,0,0),Math::Vector3i(-1,0,0),Math::Vector3i(0,1,0),Math::Vector3i(0,-1,0),Math::Vector3i(0,0,1),Math::Vector3i(0,0,-1)};
static Math::Vector2i CornerDirections [4][3] = 
	{{Math::Vector2i(-1,0),Math::Vector2i(-1,-1), Math::Vector2i(0,-1)},
	 {Math::Vector2i(0,-1),Math::Vector2i(1,-1), Math::Vector2i(1,0)},
	 {Math::Vector2i(1,0),Math::Vector2i(1, 1), Math::Vector2i(0,1)},
	 {Math::Vector2i(0,1),Math::Vector2i(-1,1), Math::Vector2i(-1,0)}};

//static Math::Vector2i EdgeDirections [4] = {Math::Vector2i(1,0),Math::Vector2i(0,1), Math::Vector2i(-1,0), Math::Vector2i(0,-1)};

static Math::Vector3i GetOffsetFromDirection (const Math::Vector2i &localoffset, const Direction &direction)
{
	return localoffset.X * direction.Tangenti () + localoffset.Y * direction.BiNormali ();
}
	 

void Chunk::FillFace (const Math::Vector3i &pos, const Direction &dir, MeshTools::MeshBuilder<Rendering::PositionTextureNormal> &builder)
{
	if (!InBounds(pos))
		return;

	const Voxel &voxel = Get(pos);

	Math::Vector3i neighborpos = pos + NeighborOffsets[dir.Index()];

	if (!InBounds(neighborpos))
		return;

	const Voxel &neighbor = Get(neighborpos);

	Math::Vector3 objectpos (pos.X,pos.Y,pos.Z);

	if (neighbor.GetFaceState(dir.Opposite()) != FaceType::Filled)
	{
		//Flat face. Perhaps apply to greedy mesher?
		auto v1 = builder.GetVertex();
		v1.Get()(objectpos + Math::Vector3(0.5f,0.5f,0.5f) + dir.TopLeftOffset (),Math::Vector2(0,0));
		auto v2 = builder.GetVertex();
		v2.Get()(objectpos + Math::Vector3(0.5f,0.5f,0.5f) + dir.TopRightOffset (),Math::Vector2(1,0));
		auto v3 = builder.GetVertex();
		v3.Get()(objectpos + Math::Vector3(0.5f,0.5f,0.5f) + dir.BottomLeftOffset (),Math::Vector2(0,1));
		auto v4 = builder.GetVertex();
		v4.Get()(objectpos + Math::Vector3(0.5f,0.5f,0.5f) + dir.BottomRightOffset (),Math::Vector2(1,1));
		auto face = builder.CreateQuad(v3,v4,v2,v1);

		face.first.FaceAwayFromPoint(objectpos + Math::Vector3(0.5f,0.5f,0.5f));
		face.second.FaceAwayFromPoint(objectpos + Math::Vector3(0.5f,0.5f,0.5f));
		
	}

}

void Chunk::Voxelize (const Math::Vector3i &pos, MeshTools::MeshBuilder<Rendering::PositionTextureNormal> &builder)
{
	const Voxel &voxel = Get(pos);

	if (voxel.IsEmpty ())
		return;

	
	Math::Vector3 objectpos (pos.X,pos.Y,pos.Z);

	if (voxel.IsFilled ())
	{
		for (int i = 0; i < 6; ++i)
		{
			FillFace(pos,Direction::FromIndex(i),builder);
		}
	}
	else //Partially filled voxel.
	{	
		Direction filldirection = Direction::FromIndex(voxel.Info.Direction);
		auto FloatVertex = builder.GetVertex ();
		//Place the vertex offset from the center based on the fill direction and amount.
		FloatVertex.Get()(objectpos + Math::Vector3(0.5f,0.5f,0.5f) + filldirection.Vector() * ((voxel.Info.Fill - 15)/31.0f), Math::Vector2(0.5f,0.5f));

		//Opposite
		FillFace (pos,filldirection.Opposite(),builder);

		float CornerFills[4] = {voxel.Info.Fill/31.0f,voxel.Info.Fill/31.0f,voxel.Info.Fill/31.0f,voxel.Info.Fill/31.0f};
		char CornerCounts[4] = {1,1,1,1};

		float CenterFills[4] = {voxel.Info.Fill/31.0f,voxel.Info.Fill/31.0f,voxel.Info.Fill/31.0f,voxel.Info.Fill/31.0f};
		char CenterCounts[4] = {1,1,1,1};

		Math::Vector3 CornerBases[4] = 
		{objectpos + Math::Vector3(0.5f,0.5f,0.5f) + filldirection.TopLeftOffset() - filldirection.Vector (),
		 objectpos + Math::Vector3(0.5f,0.5f,0.5f) + filldirection.TopRightOffset() - filldirection.Vector (),
		 objectpos + Math::Vector3(0.5f,0.5f,0.5f) + filldirection.BottomRightOffset() - filldirection.Vector (),
		 objectpos + Math::Vector3(0.5f,0.5f,0.5f) + filldirection.BottomLeftOffset() - filldirection.Vector ()};

		Math::Vector3 CenterBases[4] = 
		{(CornerBases[0] + CornerBases[1])/2,
		 (CornerBases[1] + CornerBases[2])/2,
		 (CornerBases[2] + CornerBases[3])/2,
		 (CornerBases[3] + CornerBases[0])/2};

		Vector3 filldir = filldirection.Vector();


		//Corners
		for (int c = 0; c < 4; ++c)
		{
			for (int o = 0; o < 3; ++o)
			{
				Vector3i offset = GetOffsetFromDirection(CornerDirections[c][o],filldirection);
				Math::Vector3i offsetpos = pos + offset;
				if (!InBounds(offsetpos))
				{
					continue;
				}

				const Voxel &neighborvoxel = Get(offsetpos);

				
				if (neighborvoxel.IsFilled ())
				{
					CornerFills[c] = 1;
					CornerCounts[c] = 0;
				}
				else if (neighborvoxel.IsEmpty () && CornerFills[c] != 0)
				{
					CornerFills[c] = 0;
					CornerCounts[c] = 0;
				}
				else
				{
					if (CornerCounts[c] != 0)
					{
						CornerFills[c] += neighborvoxel.Info.Fill/31.0f;
						CornerCounts[c]++;
					}
				}

				if (o == 2)
				{
					if (neighborvoxel.IsFilled ())
					{
						CenterFills[c] = 1;
						CenterCounts[c] = 0;
					}
					 else if (neighborvoxel.IsEmpty () && CenterFills[c] != 0)
					{
						CenterFills[c] = 0;
						CenterCounts[c] = 0;
					}
					else
					{
						if (CenterCounts[c] != 0)
						{
							CenterFills[c] += neighborvoxel.Info.Fill/31.0f;
							CenterCounts[c]++;
						}
					}
				}
			}
		}


		for (int i = 0; i < 4; i++)
		{
			CenterFills[i] = (CenterCounts[i] != 0 ? CenterFills[i] / CenterCounts[i] : CenterFills[i]);
			CornerFills[i] = (CornerCounts[i] != 0 ? CornerFills[i] / CornerCounts[i] : CornerFills[i]);
		}

		auto tl = builder.GetVertex ();
		tl.Get()(CornerBases[0] + filldir * CornerFills[0],Vector2(0,0));

		auto tr = builder.GetVertex ();
		tr.Get()(CornerBases[1] + filldir * CornerFills[1],Vector2(1,0));
		
		auto br = builder.GetVertex ();
		br.Get()(CornerBases[2] + filldir * CornerFills[2],Vector2(1,1));

		auto bl = builder.GetVertex ();
		bl.Get()(CornerBases[3] + filldir * CornerFills[3],Vector2(0,1));
		


		auto t = builder.GetVertex ();
		t.Get()(CenterBases[0] + filldir * CenterFills[0],Vector2(0.5f,0));

		auto r = builder.GetVertex ();
		r.Get()(CenterBases[1] + filldir * CenterFills[1],Vector2(1,0.5f));
		
		auto b = builder.GetVertex ();
		b.Get()(CenterBases[2] + filldir * CenterFills[2],Vector2(0.5f,1));

		auto l = builder.GetVertex ();
		l.Get()(CenterBases[3] + filldir * CenterFills[3],Vector2(0,0.5f));

		builder.CreateFace(tl,FloatVertex, t).FaceNormal(filldir);
		builder.CreateFace(t, FloatVertex, tr).FaceNormal(filldir);
		builder.CreateFace(tr,FloatVertex, r).FaceNormal(filldir);
		builder.CreateFace(r, FloatVertex, br).FaceNormal(filldir);
		builder.CreateFace(br,FloatVertex, b).FaceNormal(filldir);
		builder.CreateFace(b, FloatVertex, bl).FaceNormal(filldir);
		builder.CreateFace(bl,FloatVertex, l).FaceNormal(filldir);
		builder.CreateFace(l, FloatVertex, tl).FaceNormal(filldir);
		

	}
}

bool Chunk::InBounds (int x, int y, int z) const
{
	return x >= 0 && x < 16 && y >= 0 && y < 16 && z >= 0 && z < 16;
}

bool Chunk::InBounds (const Math::Vector3i &pos) const
{
	return InBounds (pos.X,pos.Y,pos.Z);
}

}}