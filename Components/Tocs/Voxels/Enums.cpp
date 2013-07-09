#include "Enums.h"

namespace Tocs {
namespace Voxels {

const Direction Direction::Left (left);
const Direction Direction::Right (right);
const Direction Direction::Up (up);
const Direction Direction::Down (down);
const Direction Direction::Forward (forward);
const Direction Direction::Backward (backward);

Direction Direction::Opposite () const
{
	InternalFormat opp;
	switch (Internal)
	{
	case left:
		opp = right;
		break;
	case right:
		opp = left;
		break;
	case forward:
		opp = backward;
		break;
	case backward:
		opp = forward;
		break;
	case up:
		opp = down;
		break;
	case down:
		opp = up;
		break;
	}

	return Direction(opp);
}


Direction Direction::FromIndex(unsigned char direction)
{
	return Direction ((InternalFormat)direction);
}

Math::Vector3 Direction::TopLeftOffset () const
{
	static Math::Vector3 directiontable [] = 
	{  
		Direction::Left.Vector ()     * 0.5f + Direction::Left.Tangent ()     * -0.5f + Direction::Left.BiNormal()     * -0.5f,
		Direction::Right.Vector ()    * 0.5f + Direction::Right.Tangent ()    * -0.5f + Direction::Right.BiNormal()    * -0.5f,
		Direction::Up.Vector ()       * 0.5f + Direction::Up.Tangent ()       * -0.5f + Direction::Up.BiNormal()       * -0.5f,
		Direction::Down.Vector ()     * 0.5f + Direction::Down.Tangent ()     * -0.5f + Direction::Down.BiNormal()     * -0.5f,
		Direction::Forward.Vector ()  * 0.5f + Direction::Forward.Tangent ()  * -0.5f + Direction::Forward.BiNormal()  * -0.5f,
		Direction::Backward.Vector () * 0.5f + Direction::Backward.Tangent () * -0.5f + Direction::Backward.BiNormal() * -0.5f,
	};
	return directiontable[Internal];
}

Math::Vector3 Direction::TopRightOffset () const
{
	static Math::Vector3 directiontable [] = 
	{  
		Direction::Left.Vector ()     * 0.5f + Direction::Left.Tangent ()     * 0.5f + Direction::Left.BiNormal()     * -0.5f,
		Direction::Right.Vector ()    * 0.5f + Direction::Right.Tangent ()    * 0.5f + Direction::Right.BiNormal()    * -0.5f,
		Direction::Up.Vector ()       * 0.5f + Direction::Up.Tangent ()       * 0.5f + Direction::Up.BiNormal()       * -0.5f,
		Direction::Down.Vector ()     * 0.5f + Direction::Down.Tangent ()     * 0.5f + Direction::Down.BiNormal()     * -0.5f,
		Direction::Forward.Vector ()  * 0.5f + Direction::Forward.Tangent ()  * 0.5f + Direction::Forward.BiNormal()  * -0.5f,
		Direction::Backward.Vector () * 0.5f + Direction::Backward.Tangent () * 0.5f + Direction::Backward.BiNormal() * -0.5f,
	};
	return directiontable[Internal];
}

Math::Vector3 Direction::BottomLeftOffset () const
{
	static Math::Vector3 directiontable [] = 
	{  
		Direction::Left.Vector ()     * 0.5f + Direction::Left.Tangent ()     * -0.5f + Direction::Left.BiNormal()     * 0.5f,
		Direction::Right.Vector ()    * 0.5f + Direction::Right.Tangent ()    * -0.5f + Direction::Right.BiNormal()    * 0.5f,
		Direction::Up.Vector ()       * 0.5f + Direction::Up.Tangent ()       * -0.5f + Direction::Up.BiNormal()       * 0.5f,
		Direction::Down.Vector ()     * 0.5f + Direction::Down.Tangent ()     * -0.5f + Direction::Down.BiNormal()     * 0.5f,
		Direction::Forward.Vector ()  * 0.5f + Direction::Forward.Tangent ()  * -0.5f + Direction::Forward.BiNormal()  * 0.5f,
		Direction::Backward.Vector () * 0.5f + Direction::Backward.Tangent () * -0.5f + Direction::Backward.BiNormal() * 0.5f,
	};
	return directiontable[Internal];
}

Math::Vector3 Direction::BottomRightOffset () const
{
	static Math::Vector3 directiontable [] = 
	{  
		Direction::Left.Vector ()     * 0.5f + Direction::Left.Tangent ()     * 0.5f + Direction::Left.BiNormal()     * 0.5f,
		Direction::Right.Vector ()    * 0.5f + Direction::Right.Tangent ()    * 0.5f + Direction::Right.BiNormal()    * 0.5f,
		Direction::Up.Vector ()       * 0.5f + Direction::Up.Tangent ()       * 0.5f + Direction::Up.BiNormal()       * 0.5f,
		Direction::Down.Vector ()     * 0.5f + Direction::Down.Tangent ()     * 0.5f + Direction::Down.BiNormal()     * 0.5f,
		Direction::Forward.Vector ()  * 0.5f + Direction::Forward.Tangent ()  * 0.5f + Direction::Forward.BiNormal()  * 0.5f,
		Direction::Backward.Vector () * 0.5f + Direction::Backward.Tangent () * 0.5f + Direction::Backward.BiNormal() * 0.5f,
	};
	return directiontable[Internal];
}

Math::Vector3 Direction::Vector () const
{
	static Math::Vector3 directiontable [] = {Math::Vector3 (-1,0,0),Math::Vector3 (1,0,0),Math::Vector3 (0,1,0),Math::Vector3 (0,-1,0),Math::Vector3 (0,0,1),Math::Vector3 (0,0,-1)};

	return directiontable[Internal];
}

Math::Vector3 Direction::Tangent () const
{
	static Math::Vector3 directiontable [] = {Math::Vector3 (0,0,-1),Math::Vector3 (0,0,1),Math::Vector3 (1,0,0),Math::Vector3 (-1,0,0),Math::Vector3 (0,1,0),Math::Vector3 (0,-1,0)};

	return directiontable[Internal];
}

Math::Vector3 Direction::BiNormal () const
{
	static Math::Vector3 directiontable [] = {Math::Vector3 (0,-1,0),Math::Vector3 (0,1,0),Math::Vector3 (0,0,1),Math::Vector3 (0,0,-1),Math::Vector3 (1,0,0),Math::Vector3 (-1,0,0)};

	return directiontable[Internal];
}

Math::Vector3i Direction::Vectori () const
{
	static Math::Vector3i directiontable [] = {Math::Vector3i (-1,0,0),Math::Vector3i (1,0,0),Math::Vector3i (0,1,0),Math::Vector3i (0,-1,0),Math::Vector3i (0,0,1),Math::Vector3i (0,0,-1)};

	return directiontable[Internal];
}

Math::Vector3i Direction::Tangenti () const
{
	static Math::Vector3i directiontable [] = {Math::Vector3i (0,0,-1),Math::Vector3i (0,0,1),Math::Vector3i (1,0,0),Math::Vector3i (-1,0,0),Math::Vector3i (0,1,0),Math::Vector3i (0,-1,0)};

	return directiontable[Internal];
}

Math::Vector3i Direction::BiNormali () const
{
	static Math::Vector3i directiontable [] = {Math::Vector3i (0,-1,0),Math::Vector3i (0,1,0),Math::Vector3i (0,0,1),Math::Vector3i (0,0,-1),Math::Vector3i (1,0,0),Math::Vector3i (-1,0,0)};

	return directiontable[Internal];
}


const FaceType FaceType::NoFill (nofill);
const FaceType FaceType::Filled (filled);
const FaceType FaceType::Augmented (augmented);

}}