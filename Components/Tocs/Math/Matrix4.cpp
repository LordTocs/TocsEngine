#include "Matrix4.h"
#include "Vector3.h"

#include <iostream>
#define a11 Data[0][0]
#define a12 Data[1][0]
#define a13 Data[2][0]
#define a14 Data[3][0]
#define a21 Data[0][1]
#define a22 Data[1][1]
#define a23 Data[2][1]
#define a24 Data[3][1]
#define a31 Data[0][2]
#define a32 Data[1][2]
#define a33 Data[2][2]
#define a34 Data[3][2]
#define a41 Data[0][3]
#define a42 Data[1][3]
#define a43 Data[2][3]
#define a44 Data[3][3]


namespace Tocs {
namespace Math {

const Matrix4 Matrix4::Identity (1);

Matrix4::Matrix4(float diagonal)
	: Data()
{
	a11 = diagonal;
	a22 = diagonal;
	a33 = diagonal;
	a44 = diagonal;
}

Matrix4::Matrix4()
	: Data ()
{
}

Matrix4 Matrix4::CreateTranslation (const Vector3 &vector)
{
	Matrix4 result;
	result.a14 = vector.X;
	result.a24 = vector.Y;
	result.a34 = vector.Z;
	return result;
}

Matrix4 Matrix4::CreateRotation (const Quaternion &rotation)
{
	Matrix4 result(1);

	float num9 = rotation.X * rotation.X;
    float num8 = rotation.Y * rotation.Y;
    float num7 = rotation.Z * rotation.Z;
    float num6 = rotation.X * rotation.Y;
    float num5 = rotation.Z * rotation.W;
    float num4 = rotation.Z * rotation.X;
    float num3 = rotation.Y * rotation.W;
    float num2 = rotation.Y * rotation.Z;
    float num =  rotation.X * rotation.W;

	result.a11 = 1 - (2 * (num8 + num7));
    result.a21 = 2 * (num6 + num5);
    result.a31 = 2 * (num4 - num3);
	 
	result.a12 = 2 * (num6 - num5);
    result.a22 = 1 - (2 * (num7 + num9));
    result.a32 = 2 * (num2 + num);

    result.a13 = 2 * (num4 + num3);
    result.a23 = 2 * (num2 - num);
    result.a33 = 1 - (2 * (num8 + num9));
   
	return result;
}

Matrix4 Matrix4::CreateLookAt (const Vector3 &Eyepoint, const Vector3 &LookPoint, const Vector3 &Up)
{
	Vector3 zaxis = (LookPoint - Eyepoint).Normalize () * -1.0f;
	Vector3 xaxis = (Up.Cross (zaxis)).Normalize ();
	Vector3 yaxis = (zaxis.Cross (xaxis)).Normalize ();

	Matrix4 result;
	result.Data[0][0] = xaxis.X;
	result.Data[1][0] = xaxis.Y;
	result.Data[2][0] = xaxis.Z;

	result.Data[0][1] = yaxis.X;
	result.Data[1][1] = yaxis.Y;
	result.Data[2][1] = yaxis.Z;

	result.Data[0][2] = zaxis.X;
	result.Data[1][2] = zaxis.Y;
	result.Data[2][2] = zaxis.Z;

	result.Data[3][0] = -(xaxis.Dot (Eyepoint));
	result.Data[3][1] = -(yaxis.Dot (Eyepoint));
	result.Data[3][2] = -(zaxis.Dot (Eyepoint));

	return result;
}

Matrix4 Matrix4::CreateLookAt (const Vector3 &EyePoint, const Vector3 &LookPoint)
{
	return CreateLookAt (EyePoint,LookPoint,Vector3(0,1,0));
}

Matrix4 Matrix4::CreateFrustum (float left, float right,float bottom, float top, float nearval, float farval)
{
	Matrix4 result (Identity);

	result.a11 = 2*nearval/(right - left);
	result.a22 = 2*nearval/(top - bottom);
	result.a33 = -(farval + nearval)/(farval - nearval);
	result.a43 = -1;
	result.a13 = (right + left)/(right - left);
	result.a23 = (top + bottom)/(top - bottom);
	result.a34 = (-2*farval * nearval)/(farval - nearval);
	result.a44 = 0;

	return result;
}

Matrix4 Matrix4::CreateProjection (float FoV, float AspectRatio, float Near, float Far)
{
	const float DEG2RAD = 2.14159265f / 180;

	float tangent = tan (FoV/2 * DEG2RAD);
	float height = Near * tangent;
	float width = height * AspectRatio;

	return Matrix4::CreateFrustum (-width,width,-height,height,Near,Far);
}

Matrix4 Matrix4::CreateRotateX (float xrot)
{
	Matrix4 result(1);
	result.a22 =  cos(xrot);
	result.a32 = -sin(xrot);
	result.a23 =  sin(xrot);
	result.a33 =  cos(xrot);
	return result;
}

Matrix4 Matrix4::CreateRotateY (float yrot)
{
	Matrix4 result(1);
	result.a11 =  cos(yrot);
	result.a13 = -sin(yrot);
	result.a31 =  sin(yrot);
	result.a33 =  cos(yrot);
	return result;
}

Matrix4 Matrix4::CreateRotateZ (float zrot)
{
	Matrix4 result(1);
	result.a11 =  cos(zrot);
	result.a21 = -sin(zrot);
	result.a12 =  sin(zrot);
	result.a22 =  cos(zrot);
	return result;
}

Matrix4 Matrix4::CreateScale (const Vector3 &scale)
{
	Matrix4 result(1);
	result.a11 = scale.X;
	result.a22 = scale.Y;
	result.a33 = scale.Z;
	return result;
}

Matrix4 Matrix4::Inversion (const Matrix4 &matrix)
{
	float c11 =  ((matrix.a22 * (matrix.a33 * matrix.a44 - matrix.a43 * matrix.a34)) - (matrix.a23 * (matrix.a32 * matrix.a44 - matrix.a42 * matrix.a34)) + (matrix.a24 * (matrix.a32 * matrix.a43 - matrix.a42 * matrix.a33)));
	float c12 = -((matrix.a23 * (matrix.a34 * matrix.a41 - matrix.a44 * matrix.a31)) - (matrix.a24 * (matrix.a33 * matrix.a41 - matrix.a43 * matrix.a31)) + (matrix.a21 * (matrix.a33 * matrix.a44 - matrix.a43 * matrix.a34)));
	float c13 =  ((matrix.a24 * (matrix.a31 * matrix.a42 - matrix.a41 * matrix.a32)) - (matrix.a21 * (matrix.a34 * matrix.a42 - matrix.a44 * matrix.a32)) + (matrix.a22 * (matrix.a34 * matrix.a41 - matrix.a44 * matrix.a31)));
	float c14 = -((matrix.a21 * (matrix.a32 * matrix.a43 - matrix.a42 * matrix.a33)) - (matrix.a22 * (matrix.a31 * matrix.a43 - matrix.a41 * matrix.a33)) + (matrix.a23 * (matrix.a31 * matrix.a42 - matrix.a41 * matrix.a32)));
	float d = matrix.a11 * c11 + matrix.a12 * c12 + matrix.a13 * c13 + matrix.a14 * c14;
	//printf ("d: %f\na12: %f\na13: %f\na14: %f\nc11: %f\nc12: %f\nc13: %f\nc14: %f\n",d,a12,a13,a14,c11,c12,c13,c14);
	Matrix4 Result;
	Result.Data[0][0] = c11 / d;
	Result.Data[0][1] = c12 / d;
	Result.Data[0][2] = c13 / d;
	Result.Data[0][3] = c14 / d;
	Result.Data[1][0] = -((matrix.a32 * (matrix.a43 * matrix.a14 - matrix.a13 * matrix.a44)) - (matrix.a33 * (matrix.a42 * matrix.a14 - matrix.a12 * matrix.a44)) + (matrix.a34 * (matrix.a42 * matrix.a13 - matrix.a12 * matrix.a43))) / d;
	Result.Data[1][1] =  ((matrix.a33 * (matrix.a44 * matrix.a11 - matrix.a14 * matrix.a41)) - (matrix.a34 * (matrix.a43 * matrix.a11 - matrix.a13 * matrix.a41)) + (matrix.a31 * (matrix.a43 * matrix.a14 - matrix.a13 * matrix.a44))) / d;
	Result.Data[1][2] = -((matrix.a34 * (matrix.a41 * matrix.a12 - matrix.a11 * matrix.a42)) - (matrix.a31 * (matrix.a44 * matrix.a12 - matrix.a14 * matrix.a42)) + (matrix.a32 * (matrix.a44 * matrix.a11 - matrix.a14 * matrix.a41))) / d;
	Result.Data[1][3] =  ((matrix.a31 * (matrix.a42 * matrix.a13 - matrix.a12 * matrix.a43)) - (matrix.a32 * (matrix.a41 * matrix.a13 - matrix.a11 * matrix.a43)) + (matrix.a33 * (matrix.a41 * matrix.a12 - matrix.a11 * matrix.a42))) / d;
	Result.Data[2][0] =  ((matrix.a42 * (matrix.a13 * matrix.a24 - matrix.a23 * matrix.a14)) - (matrix.a43 * (matrix.a12 * matrix.a24 - matrix.a22 * matrix.a14)) + (matrix.a44 * (matrix.a12 * matrix.a23 - matrix.a22 * matrix.a13))) / d;
	Result.Data[2][1] = -((matrix.a43 * (matrix.a14 * matrix.a21 - matrix.a24 * matrix.a11)) - (matrix.a44 * (matrix.a13 * matrix.a21 - matrix.a23 * matrix.a11)) + (matrix.a41 * (matrix.a13 * matrix.a24 - matrix.a23 * matrix.a14))) / d;
	Result.Data[2][2] =  ((matrix.a44 * (matrix.a11 * matrix.a22 - matrix.a21 * matrix.a12)) - (matrix.a41 * (matrix.a14 * matrix.a22 - matrix.a24 * matrix.a12)) + (matrix.a42 * (matrix.a14 * matrix.a21 - matrix.a24 * matrix.a11))) / d;
	Result.Data[2][3] = -((matrix.a41 * (matrix.a12 * matrix.a23 - matrix.a22 * matrix.a13)) - (matrix.a42 * (matrix.a11 * matrix.a23 - matrix.a21 * matrix.a13)) + (matrix.a43 * (matrix.a11 * matrix.a22 - matrix.a21 * matrix.a12))) / d;
	Result.Data[3][0] = -((matrix.a12 * (matrix.a23 * matrix.a34 - matrix.a33 * matrix.a24)) - (matrix.a13 * (matrix.a22 * matrix.a34 - matrix.a32 * matrix.a24)) + (matrix.a14 * (matrix.a22 * matrix.a33 - matrix.a32 * matrix.a23))) / d;
	Result.Data[3][1] =  ((matrix.a13 * (matrix.a24 * matrix.a31 - matrix.a34 * matrix.a21)) - (matrix.a14 * (matrix.a23 * matrix.a31 - matrix.a33 * matrix.a21)) + (matrix.a11 * (matrix.a23 * matrix.a34 - matrix.a33 * matrix.a24))) / d;
	Result.Data[3][2] = -((matrix.a14 * (matrix.a21 * matrix.a32 - matrix.a31 * matrix.a22)) - (matrix.a11 * (matrix.a24 * matrix.a32 - matrix.a34 * matrix.a22)) + (matrix.a12 * (matrix.a24 * matrix.a31 - matrix.a34 * matrix.a21))) / d;
	Result.Data[3][3] =  ((matrix.a11 * (matrix.a22 * matrix.a33 - matrix.a32 * matrix.a23)) - (matrix.a12 * (matrix.a21 * matrix.a33 - matrix.a31 * matrix.a23)) + (matrix.a13 * (matrix.a21 * matrix.a32 - matrix.a31 * matrix.a22))) / d;

	return Result;
}

Matrix4 operator* (const Matrix4 &op1, const Matrix4 &op2)
{
	Matrix4 result;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				result(i,j) += op1(i,k) * op2(k,j);
			}
		}
	}

	return result;
}
Matrix4 operator* (const Matrix4 &op1, float op2)
{
	Matrix4 result;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result(i,j) = op1(i,j) * op2;
		}
	}

	return result;
}
Matrix4 operator* (float op1, const Matrix4 &op2)
{
	Matrix4 result;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result(i,j) = op1 * op2(i,j);
		}
	}

	return result;
}
Matrix4 operator/ (const Matrix4 &op1, float op2)
{
	Matrix4 result;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result(i,j) = op1(i,j) / op2;
		}
	}

	return result;
}
Matrix4 operator+ (const Matrix4 &op1, const Matrix4 &op2)
{
	Matrix4 result;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result(i,j) = op1(i,j) + op2(i,j);
		}
	}

	return result;
}
Matrix4 operator- (const Matrix4 &op1, const Matrix4 &op2)
{
	Matrix4 result;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result(i,j) = op1(i,j) - op2(i,j);
		}
	}

	return result;
}
Vector3 operator* (const Matrix4 &op1, const Vector3 &op2)
{
	Vector3 result;

	result.X = op2.X * op1(0,0) + op2.Y * op1(0,1) + op2.Z * op1(0,2) + op1(0,3);
	result.Y = op2.X * op1(1,0) + op2.Y * op1(1,1) + op2.Z * op1(1,2) + op1(1,3);
	result.Z = op2.X * op1(2,0) + op2.Y * op1(2,1) + op2.Z * op1(2,2) + op1(2,3);

	return result;
}

}}