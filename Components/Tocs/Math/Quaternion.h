#pragma once
#include "Vector.h"

namespace Tocs {
namespace Math {

class Quaternion
{
public:
	float X,Y,Z,W;
	Quaternion();

	float Magnitude () const;
	Quaternion &Normalize ();

	float Dot (const Quaternion &op2) const;

	static Quaternion Slerp (const Quaternion &start, const Quaternion &finish, float t);
	static Quaternion FromEuler (float x, float y, float z);
	static Quaternion FromEuler (const Vector3 &euler);
};

Quaternion operator*(const Quaternion &op1, const Quaternion &op2);
Quaternion operator*(float op1, const Quaternion &op2);
Quaternion operator*(const Quaternion &op1, float op2);
Quaternion operator/(const Quaternion &op1, float op2);
Quaternion operator+(const Quaternion &op1, const Quaternion &op2);
Quaternion operator-(const Quaternion &op1, const Quaternion &op2);


}}