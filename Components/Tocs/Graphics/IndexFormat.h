#pragma once

namespace Tocs {
namespace Graphics {

class IndexFormat
{
	enum InternalFormat
	{
		sixteenbit = 0x1403,
		thirtytwobit = 0x1405
	};
	InternalFormat Internal;

	IndexFormat(InternalFormat format)
		: Internal(format) {}
public:
	const static IndexFormat SixteenBit;
	const static IndexFormat ThirtyTwoBit;

	int GetGLEnum() const;
	unsigned int SizeInBytes() const { return (Internal == sixteenbit ? 2 : 4); }

	bool operator ==  (const IndexFormat &op2) const { return Internal == op2.Internal; }
	bool operator !=  (const IndexFormat &op2) const { return Internal != op2.Internal; }

	template <class T>
	static IndexFormat FromType();

	template<>
	static IndexFormat FromType<unsigned int>() { return ThirtyTwoBit; }

	template<>
	static IndexFormat FromType<unsigned short>() { return SixteenBit; }
};

}}