#pragma once
#include <iostream>
#include "Quaternion.h"
#include "Vector.h"
namespace Tocs {
namespace Math {


//[1 0 0 x] [0 4 8  12]
//[0 1 0 y] [1 5 9  13]
//[0 0 1 z]	[2 6 10 14]
//[0 0 0 1]	[3 7 11 15]

class Matrix4
{
	float Data [16];
	Matrix4(float diagonal);
public:
	static const Matrix4 Identity;
	Matrix4();

	float &operator()(int row, int column) { return Data[column * 4 + row]; }
	const float &operator()(int row, int column) const { return Data[column * 4 + row]; }

	void Invert ();
	void Translate (const Vector3 &vector);

	static Matrix4 CreateTranslation (const Vector3 &vector);
	static Matrix4 CreateRotation (const Quaternion &rotation);
	static Matrix4 CreateScale (const Vector3 &scale);
	static Matrix4 CreateScale (float x, float y, float z);

	static Matrix4 CreateLookAt (const Vector3 &Eyepoint, const Vector3 &LookPoint);
	static Matrix4 CreateLookAt (const Vector3 &Eyepoint, const Vector3 &LookPoint, const Vector3 &Up);

	static Matrix4 CreateFrustum (float left, float right,float bottom, float top, float nearval, float farval);
	static Matrix4 CreateProjection (float FoV, float AspectRatio, float Near, float Far);
	
	static Matrix4 CreateRotateX (float xrot);
	static Matrix4 CreateRotateY (float yrot);
	static Matrix4 CreateRotateZ (float zrot);

	static Matrix4 Inversion (const Matrix4 &matrix);

	float *GetData () const { return (float *)&(Data[0]); }
};

Matrix4 operator* (const Matrix4 &op1, const Matrix4 &op2);
Matrix4 operator* (const Matrix4 &op1, float op2);
Matrix4 operator* (float op1, const Matrix4 &op2);
Matrix4 operator/ (const Matrix4 &op1, float op2);
Matrix4 operator+ (const Matrix4 &op1, const Matrix4 &op2);
Matrix4 operator- (const Matrix4 &op1, const Matrix4 &op2);
Vector3 operator* (const Matrix4 &op1, const Vector3 &op2);
std::ostream &operator<< (std::ostream &stream, const Matrix4 &mat);
}}