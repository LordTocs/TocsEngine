#pragma once
#include "Vector.h"
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
	explicit Transform(Vector3 position);

	const Matrix4 &GetMatrix () const { return TransformMatrix; }

	void CreateMatrix ();


	Vector3 GetWorldPosition ();
};

}}