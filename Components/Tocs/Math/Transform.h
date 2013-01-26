#pragma once
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix4.h"
namespace Tocs {
namespace Math {

class Transform
{
	Matrix4 TransformMatrix;
public:
	Vector3 Position;
	Quaternion Rotation;
	Vector3 Scale;

	Transform();

	const Matrix4 &GetMatrix () const { return TransformMatrix; }

	void CreateMatrix ();
};

}}