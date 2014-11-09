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
	std::vector<unsigned int> TextureData;
	MeshTools::MeshBuilder<VoxelVertex> builder;
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
	builder.ComputeSmoothNormals();
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
	result.Materials[0] = voxel.Info.Id;
	result.MaterialWeights[0] = 1.0;
	result.BottomMaterials[0] = voxel.Info.Id;
	result.BottomMaterialWeights[0] = 1.0;

	if (corner)
	{
		Vector3i vertexoffset = voxel.GetDirection().CornerOffset(index / 2);

		//Step one. Collect point data for the ring of vertices we're trying to generate.
		for (int i = 0; i < 3; ++i) //iterate neighboring
		{
			Vector3i neighboroffset = GetOffsetFromDirection(CornerDirections[index / 2][i], voxel.GetDirection());
			CollectNeighborInfo(posi, neighboroffset, vertexoffset, result);
		}
		//Step two adjust for possible offsets
		AdjustOffset(posi, vertexoffset, result);

		//Determine materials
	}
	else
	{
		Vector3i vertexoffset = voxel.GetDirection().CenterOffset(index / 2);
		Vector3i neighboroffset = GetOffsetFromDirection(CornerDirections[index / 2][2], voxel.GetDirection());
		CollectNeighborInfo(posi, neighboroffset, vertexoffset, result);
		AdjustOffset(posi, vertexoffset, result);
	}

	return result;
}

void Chunk::Voxelize(const Math::Vector3i &posi, MeshTools::MeshBuilder<VoxelVertex> &builder)
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


bool Chunk::InBounds (int x, int y, int z) const
{
	return x >= 0 && x < 16 && y >= 0 && y < 16 && z >= 0 && z < 16;
}

bool Chunk::InBounds (const Math::Vector3i &pos) const
{
	return InBounds (pos.X,pos.Y,pos.Z);
}

}}