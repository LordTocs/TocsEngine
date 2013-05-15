#pragma once
#include<Tocs/Rendering/Mesh.h>
#include "Tile.h"
#include <memory>

namespace Tocs {

class TileGrid
{
	std::unique_ptr<Tile []> Tiles;
	int Width, Height;
	int GetIndex(int x, int y) const { return x + y * Width; }
	bool InBounds(int x, int y) const { return x >= 0 && x < Width && y >= 0 && y < Height; }
public:
	TileGrid(int width, int height);

	Tile &GetTile (int x, int y) { return Tiles[x + y * Width]; }
	const Tile &GetTile (int x, int y) const { return Tiles[x + y * Width]; }
	const Tile &operator()(int x, int y) const { return Tiles[x + y * Width]; }
	Tile &operator()(int x, int y) { return Tiles[x + y * Width]; }

	Rendering::Mesh GenerateMesh ();
};

}