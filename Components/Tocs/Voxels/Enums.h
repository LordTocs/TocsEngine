#pragma once
#include <string>
#include <Tocs/Math/Vector.h>
namespace Tocs {
namespace Voxels {

class Direction
{
	enum InternalFormat : unsigned char
	{
		left,
		right,
		up,
		down,
		forward,
		backward
	};
	Direction (InternalFormat format)
		: Internal(format) {}

	InternalFormat Internal;
public:
	const static Direction Left;
	const static Direction Right;
	const static Direction Up;
	const static Direction Down;
	const static Direction Forward;
	const static Direction Backward;

	std::string ToString () const;

	bool operator ==  (const Direction &op2) const {return Internal == op2.Internal;}
	bool operator !=  (const Direction &op2) const {return Internal != op2.Internal;}

	Direction Opposite() const;
	unsigned char Index() const { return (unsigned char)Internal; }

	static Direction FromIndex(unsigned char direction);

	Math::Vector3 TopLeftOffset () const;
	Math::Vector3 TopRightOffset () const;
	Math::Vector3 BottomLeftOffset () const;
	Math::Vector3 BottomRightOffset () const;

	Math::Vector3 Vector () const;
	Math::Vector3 Tangent () const;
	Math::Vector3 BiNormal () const;

	Math::Vector3i Vectori () const;
	Math::Vector3i Tangenti () const;
	Math::Vector3i BiNormali () const;
};

class FaceType
{
	enum InternalFormat : unsigned char
	{
		nofill,
		filled,
		augmented
	};

	FaceType (InternalFormat format)
		: Internal(format) {}

	InternalFormat Internal;
public:
	const static FaceType NoFill;
	const static FaceType Filled;
	const static FaceType Augmented;

	bool operator ==  (const FaceType &op2) const {return Internal == op2.Internal;}
	bool operator !=  (const FaceType &op2) const {return Internal != op2.Internal;}
};

}}