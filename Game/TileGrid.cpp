#include "TileGrid.h"
#include <Tocs/Rendering/Vertices.h>
#include <Tocs/MeshTools/MeshBuilder.h>
#include <Tocs/MeshTools/GreedyTileMesher.h>
namespace Tocs {
/*
TileGrid::TileGrid(int width, int height)
	: Width(width), Height(height),
	  Tiles(new Tile[width * height])
{
}


Rendering::Mesh TileGrid::GenerateMesh ()
{
	MeshTools::MeshBuilder<Rendering::PositionTextureNormal> mesh;
	MeshTools::GreedyTileMesher floormesher (Width,Height);
	for (int y = 0; y < Height; ++y)
	{
		for (int x = 0; x < Width; ++x)
		{
			floormesher(x,y) = MeshTools::TileMask(GetTile(x,y).Type == TileType::Air);
		}
	}

	//floor
	floormesher.Generate(Math::Vector3(0,0,0),Math::Vector3(1,0,0),Math::Vector3(0,0,1),Math::Vector3(0,1,0),mesh);

	for (int y = 0; y < Height; ++y)
	{
		for (int x = 0; x < Width; ++x)
		{
			floormesher(x,y) = MeshTools::TileMask(GetTile(x,y).Type == TileType::Air);
		}
	}
	//ceiling
	floormesher.Generate(Math::Vector3(0,2.5f,0),Math::Vector3(1,0,0),Math::Vector3(0,0,1),Math::Vector3(0,-1,0),mesh);

	MeshTools::GreedyTileMesher xwallmesher (Width,1);

	//Back walls
	for (int y = 0; y < Height; ++y)
	{
		for (int x = 0; x < Width; ++x)
		{
			if (!InBounds(x,y-1))
				xwallmesher(x,0).HasFace = GetTile(x,y).Type == TileType::Air;
			else
				xwallmesher(x,0).HasFace = GetTile(x,y).Type == TileType::Air && GetTile(x,y - 1).Type == TileType::Solid;
		}

		xwallmesher.Generate(Math::Vector3(0,0,y),Math::Vector3(1,0,0),Math::Vector3(0,2.5f,0),Math::Vector3(0,0,1),mesh);
	}
	//Forward walls
	for (int y = 0; y < Height; ++y)
	{
		for (int x = 0; x < Width; ++x)
		{
			if (!InBounds(x,y+1))
				xwallmesher(x,0).HasFace = GetTile(x,y).Type == TileType::Air;
			else
				xwallmesher(x,0).HasFace = GetTile(x,y).Type == TileType::Air && GetTile(x,y + 1).Type == TileType::Solid;
		}

		xwallmesher.Generate(Math::Vector3(0,0,y+1),Math::Vector3(1,0,0),Math::Vector3(0,2.5f,0),Math::Vector3(0,0,-1),mesh);
	}

	MeshTools::GreedyTileMesher zwallmesher(Height,1);

	//Forward facing walls
	for (int x = 0; x < Width; ++x)
	{
		for (int y = 0; y < Height; ++y)
		{
			if (!InBounds(x-1,y))
				zwallmesher(y,0).HasFace = GetTile(x,y).Type == TileType::Air;
			else
				zwallmesher(y,0).HasFace = GetTile(x,y).Type == TileType::Air && GetTile(x-1,y).Type == TileType::Solid;
		}

		zwallmesher.Generate(Math::Vector3(x,0,0),Math::Vector3(0,0,1),Math::Vector3(0,2.5f,0),Math::Vector3(1,0,0),mesh);
	}
	//Backward facing walls
	for (int x = 0; x < Width; ++x)
	{
		for (int y = 0; y < Height; ++y)
		{
			if (!InBounds(x+1,y))
				zwallmesher(y,0).HasFace = GetTile(x,y).Type == TileType::Air;
			else
				zwallmesher(y,0).HasFace = GetTile(x,y).Type == TileType::Air && GetTile(x+1,y).Type == TileType::Solid;
		}

		zwallmesher.Generate(Math::Vector3(x+1,0,0),Math::Vector3(0,0,1),Math::Vector3(0,2.5f,0),Math::Vector3(-1,0,0),mesh);
	}

	mesh.ComputeNormals();
	return std::move(mesh.CreateMesh());
}

*/
}