#pragma once
#include <string>

namespace Tocs {

class TileType
{
	enum InternalFormat
	{
		solid,
		air
	};
	InternalFormat Internal;

	TileType (InternalFormat format)
		: Internal (format) {}

public:
	const static TileType Solid;
	const static TileType Air;

	bool operator == (const TileType &op2) const {return Internal == op2.Internal;}
	bool operator != (const TileType &op2) const {return Internal != op2.Internal;}
	bool operator <  (const TileType &op2) const {return Internal <  op2.Internal; }

	std::string ToString () const;	
};

class Tile
{
public:
	TileType Type;

	Tile () : Type (TileType::Solid) {}
};

}


