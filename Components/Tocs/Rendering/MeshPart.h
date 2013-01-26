#pragma once

namespace Tocs {
namespace Rendering {

class MeshPart
{
	unsigned int Offset;
	unsigned int Length;
public:
	MeshPart (unsigned int offset, unsigned int length)
		: Offset(offset), Length(length)
	{}

	unsigned int GetOffset () const { return Offset; }
	unsigned int GetLength () const { return Length; }
};


}}
