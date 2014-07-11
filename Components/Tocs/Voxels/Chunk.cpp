#include "Chunk.h"
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

static Math::Vector3 LocalVertexColumns[8] =
{
	Math::Vector3(-0.5f, -0.5f, -0.5f),
	Math::Vector3(0, -0.5f, -0.5f),
	Math::Vector3(0.5f, -0.5f, -0.5f),
	Math::Vector3(0.5f, -0.5f, 0),
	Math::Vector3(0.5f, -0.5f, 0.5f),
	Math::Vector3(0, -0.5f, 0.5f),
	Math::Vector3(-0.5f, -0.5f, 0.5f),
	Math::Vector3(-0.5f, -0.5f, 0)
};

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

void Chunk::CollectNeighborInfo(const Math::Vector3i &posi, const Math::Vector3i &offset, const Math::Vector3i &vertoffset, PointInfo &result) const
{
	const Voxel &voxel = Get(posi);

	if (!InBounds(posi + offset))
	{
		result.HasBottom = true;
		return;
	}

	const Voxel &neighbor = Get(posi + offset);

	if (neighbor.IsPartial())
	{
		if (neighbor.GetDirection() == voxel.GetDirection())
		{
			result.FillSum += neighbor.FillNorm();
			++result.FillAverageCount;
		}
		else
		{
			int OdD = offset.Dot(neighbor.GetDirection().Vectori());
			if (OdD > 0)
			{
				//Corner is at the "Back of some opposite direction"
				result.HasTop = true;
			}
			else if (OdD < 0)
			{
				//Neighbor is pointing "into" the current voxel
				//If the neighbor has a support face it will match the float of this polygon
				//If it doesn't we have a bottom vertice
				Vector3i downpos = posi + offset - voxel.GetDirection().Vectori();
				if (InBounds(downpos))
				{
					const Voxel &wallvoxel = Get(downpos);
					if (!(wallvoxel.GetDirection().Opposite() == voxel.GetDirection() || wallvoxel.IsFilled())) //There isn't a wall face 
					{
						result.HasBottom = true;
					}
				}
			}
			else if (OdD == 0)
			{
				//int VdD = vertoffset.Dot(neighbor.GetDirection().Vectori());
				result.HasBottom = true;
			}
		}

	}
	else if (neighbor.IsEmpty())
	{
		result.HasBottom = true;
	}
	else if (neighbor.IsFilled())
	{
		result.HasTop = true;
	}
}

void Chunk::AdjustOffset(const Math::Vector3i &pos, const Math::Vector3i &vertoffset, PointInfo &result) const
{
	const Voxel &voxel = Get(pos);
	//Step two if this voxel points "into" another and can be smoothed we offset the vertices to smooth.
	if (!result.HasTop)
	{
		return;
	}

	Vector3i forwardpos = voxel.GetDirection().Vectori() + pos;
	if (!InBounds(forwardpos))
	{
		return;
	}
	const Voxel &forward = Get(forwardpos);

	if (forward.IsEmpty())
	{
		return;
	}
	
	Vector3i forwarddir = forward.GetDirection().Vectori();

	int FdD = forwarddir.Dot(vertoffset);
	if (FdD >= 0)
	{
		return;
	}

	//We might an offset!
	Vector3i neighboroffset = vertoffset + forwarddir;

	if (neighboroffset.LengthSquared() != 0)
	{
		//There's a neighbor we have to check to see if we can offset.
		Vector3i neighborpos = pos + neighboroffset;
		//We have a neighbor to check
		if (InBounds(neighborpos))
		{
			const Voxel &neighbor = Get(neighborpos);
			if (neighbor.GetDirection() == voxel.GetDirection())
			{
				//Neighbor's forward in the same direction
				if (InBounds(neighborpos + voxel.GetDirection().Vectori()))
				{
					const Voxel &fneighbor = Get(neighborpos + voxel.GetDirection().Vectori());
					if (fneighbor.GetDirection() == forward.GetDirection())
					{
						//Is there a support face?
						if (InBounds(neighborpos - forwarddir))
						{
							const Voxel &sneighbor = Get(neighborpos - forwarddir);
							if (!sneighbor.IsEmpty() && (sneighbor.IsFilled() || sneighbor.GetDirection().Vectori().Dot(forwarddir) > 0))
							{
								//There's a support face, and everythings in the correct direction.
								//Offset is go
								float offsetavg = (forward.FillNorm() + fneighbor.FillNorm()) / 2;
								result.Offset = forward.GetDirection().Vector() * offsetavg;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		//no neighbors to check
		result.Offset = forward.GetDirection().Vector() * forward.FillNorm();
	}
}

Chunk::PointInfo Chunk::GetPointInfo(const Math::Vector3i &posi, unsigned int index) const
{
	const Voxel &voxel = Get(posi);

	bool corner = (index % 2 == 0); //Alternate between corners and centerpoints

	Vector3i forwardpos = posi + voxel.GetDirection().Vectori();

	PointInfo result;
	result.FillAverageCount = 1;
	result.FillSum = voxel.FillNorm();

	if (corner)
	{
		Vector3i cornerdir = voxel.GetDirection().CornerOffset(index / 2);

		//Step one. Collect point data for the ring of vertices we're trying to generate.
		for (int i = 0; i < 3; ++i) //iterate neighboring
		{
			Vector3i offset = GetOffsetFromDirection(CornerDirections[index/2][i], voxel.GetDirection());
			CollectNeighborInfo(posi, offset, cornerdir, result);
		}

		AdjustOffset(posi, cornerdir, result);
	}
	else
	{
		Vector3i middledir = voxel.GetDirection().CenterOffset(index / 2);
		Vector3i offset = GetOffsetFromDirection(CornerDirections[index / 2][2], voxel.GetDirection());
		CollectNeighborInfo(posi, offset, middledir, result);
		AdjustOffset(posi, middledir, result);
	}

	return result;
}

void Chunk::Voxelize(const Math::Vector3i &posi, MeshTools::MeshBuilder<Rendering::PositionTextureNormal> &builder)
{
	const Voxel &voxel = Get(posi);

	if (voxel.IsFilled())
		return;

	if (voxel.IsEmpty())
	{

		return;
	}


	Math::Vector3 centerpos(posi.X + 0.5f, posi.Y + 0.5f, posi.Z + 0.5f);

	auto centervertex = builder.GetVertex();
	Math::Vector3 centervertexpos = centerpos + voxel.GetDirection().Vector() * (voxel.FillNorm() - 0.5f);
	centervertex.Get().Position = centervertexpos;

	Direction filldirection = Direction::FromIndex(voxel.Info.Direction);

	 std::vector<Math::Vector3> ringvertices;

	PointInfo points[8];
	for (unsigned int i = 0; i < 8; ++i)
	{
		points[i] = GetPointInfo(posi, i);
	}

	for (int i = 0; i < 8; ++i)
	{
		const PointInfo &current = points[i];
		const PointInfo &prev = points[(i - 1 >= 0 ? i - 1 : 7)];
		
		Math::Vector3 basepos = voxel.Globalize(LocalVertexColumns[i]) + centerpos;

		if (current.HasTop || current.HasBottom)
		{
			Math::Vector3 toppos = basepos + voxel.GetDirection().Vector() + current.Offset;
			if (prev.HasTop && current.HasTop)
			{
				//emit top vertex first
				ringvertices.push_back(toppos);
			}
			if (prev.HasBottom && current.HasBottom)
			{
				//emit bottom vertex first
				ringvertices.push_back(basepos);
			}
			if (!prev.HasTop && current.HasTop)
			{
				//emit the top vertex second
				ringvertices.push_back(toppos);
			}
			if (!prev.HasBottom && current.HasBottom)
			{
				//emit the bottom vertex second  
				ringvertices.push_back(basepos);
			}
			
		}
		else
		{
			//emit floating vertex
			Math::Vector3 floatpos = basepos + voxel.GetDirection().Vector() * (current.FillSum / current.FillAverageCount);
			ringvertices.push_back(floatpos);
		}
	}

	//Convert ring vertices into triangles
	auto first = builder.GetVertex();
	first.Get().Position = ringvertices[0];

	auto prev = first;

	for (int i = 1; i < ringvertices.size(); ++i)
	{
		auto vert = builder.GetVertex();
		vert.Get().Position = ringvertices[i];
		auto f = builder.CreateFace(vert, prev, centervertex);
		if (voxel.GetDirection() == Direction::Left || voxel.GetDirection() == Direction::Down || voxel.GetDirection() == Direction::Backward)
		{
			f.FlipOrder();
		}
		prev = vert;
	}


	auto f = builder.CreateFace(first, prev, centervertex);
	if (voxel.GetDirection() == Direction::Left || voxel.GetDirection() == Direction::Down || voxel.GetDirection() == Direction::Backward)
	{
		f.FlipOrder();
	}
}


/*
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
		{(CornerBases[0] + CornerBases[1]) / 2.0f,
		 (CornerBases[1] + CornerBases[2]) / 2.0f,
		 (CornerBases[2] + CornerBases[3]) / 2.0f,
		 (CornerBases[3] + CornerBases[0]) / 2.0f};

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
}*/

bool Chunk::InBounds (int x, int y, int z) const
{
	return x >= 0 && x < 16 && y >= 0 && y < 16 && z >= 0 && z < 16;
}

bool Chunk::InBounds (const Math::Vector3i &pos) const
{
	return InBounds (pos.X,pos.Y,pos.Z);
}

}}