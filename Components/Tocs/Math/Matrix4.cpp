#include "Matrix4.h"
#include "Vector3.h"

#include <iostream>
#define a11 Data[0]
#define a12 Data[4]
#define a13 Data[8]
#define a14 Data[12]
#define a21 Data[1]
#define a22 Data[5]
#define a23 Data[9]
#define a24 Data[13]
#define a31 Data[2]
#define a32 Data[6]
#define a33 Data[10]
#define a34 Data[14]
#define a41 Data[3]
#define a42 Data[7]
#define a43 Data[11]
#define a44 Data[15]

//[1 0 0 x] [0 4 8  12]
//[0 1 0 y] [1 5 9  13]
//[0 0 1 z]	[2 6 10 14]
//[0 0 0 1]	[3 7 11 15]

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
	result(0,3) = vector.X;
	result(1,3) = vector.Y;
	result(2,3) = vector.Z;
	return result;
}

Matrix4 Matrix4::CreateRotation (const Quaternion &rotation)
{
	Matrix4 result(1);

	float xx = rotation.X * rotation.X;
    float yy = rotation.Y * rotation.Y;
    float zz = rotation.Z * rotation.Z;
    float xy = rotation.X * rotation.Y;
    float zw = rotation.Z * rotation.W;
    float zx = rotation.Z * rotation.X;
    float yw = rotation.Y * rotation.W;
    float yz = rotation.Y * rotation.Z;
    float xw =  rotation.X * rotation.W;

	result(0,0) = 1 - (2 * (yy + zz));
    result(1,0) = 2 * (xy + zw);
    result(2,0) = 2 * (zx - yw);
	 
	result(0,1) = 2 * (xy - zw);
    result(1,1) = 1 - (2 * (xx + zz));
    result(2,1) = 2 * (yz + xw);

    result(0,2) = 2 * (zx + yw);
    result(1,2) = 2 * (yz - xw);
    result(2,2) = 1 - (2 * (xx + yy));
   
	return result;
}



Matrix4 Matrix4::CreateLookAt (const Vector3 &Eyepoint, const Vector3 &LookPoint, const Vector3 &Up)
{
	Vector3 zaxis = (Eyepoint - LookPoint).Normalize ();
	Vector3 xaxis = (Up.Cross (zaxis)).Normalize ();
	Vector3 yaxis = (zaxis.Cross (xaxis)).Normalize ();

	Matrix4 result(1);
	result(0,0) = xaxis.X;
	result(1,0) = xaxis.Y;
	result(2,0) = xaxis.Z;

	result(0,1) = yaxis.X;
	result(1,1) = yaxis.Y;
	result(2,1) = yaxis.Z;

	result(0,2) = zaxis.X;
	result(1,2) = zaxis.Y;
	result(2,2) = zaxis.Z;

	result(0,3) = -(xaxis.Dot (Eyepoint));
	result(1,3) = -(yaxis.Dot (Eyepoint));
	result(2,3) = -(zaxis.Dot (Eyepoint));

	return result;
}

Matrix4 Matrix4::CreateLookAt (const Vector3 &EyePoint, const Vector3 &LookPoint)
{
	return CreateLookAt (EyePoint,LookPoint,Vector3(0,1,0));
}

Matrix4 Matrix4::CreateFrustum (float left, float right,float bottom, float top, float nearval, float farval)
{
	Matrix4 result (Identity);

	result(0,0) = 2*nearval/(right - left);
	result(1,1) = 2*nearval/(top - bottom);
	result(2,2) = -(farval + nearval)/(farval - nearval);
	result(3,2) = -1;
	result(0,2) = (right + left)/(right - left);
	result(1,2) = (top + bottom)/(top - bottom);
	result(2,3) = (-2*farval * nearval)/(farval - nearval);
	result(3,3) = 0;

	return result;
}

Matrix4 Matrix4::CreateProjection (float FoV, float AspectRatio, float Near, float Far)
{
	float tangent = tan (FoV/2);
	float height = Near * tangent;
	float width = height * AspectRatio;

	return Matrix4::CreateFrustum (-width,width,-height,height,Near,Far);
}

Matrix4 Matrix4::CreateRotateX (float xrot)
{
	Matrix4 result(1);
	result(1,1) =  cos(xrot);
	result(2,1) = -sin(xrot);
	result(1,2) =  sin(xrot);
	result(2,2) =  cos(xrot);
	return result;
}

Matrix4 Matrix4::CreateRotateY (float yrot)
{
	Matrix4 result(1);
	result(0,0) =  cos(yrot);
	result(0,2) = -sin(yrot);
	result(2,0) =  sin(yrot);
	result(2,2) =  cos(yrot);
	return result;
}

Matrix4 Matrix4::CreateRotateZ (float zrot)
{
	Matrix4 result(1);
	result(0,0) =  cos(zrot);
	result(1,0) = -sin(zrot);
	result(0,1) =  sin(zrot);
	result(1,1) =  cos(zrot);
	return result;
}

Matrix4 Matrix4::CreateScale (float x, float y, float z)
{
	Matrix4 result(1);
	result(0,0) = x;
	result(1,1) = y;
	result(2,2) = z;
	return result;
}

Matrix4 Matrix4::CreateScale (const Vector3 &scale)
{
	Matrix4 result(1);
	result(0,0) = scale.X;
	result(1,1) = scale.Y;
	result(2,2) = scale.Z;
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
	Result(0,0) = c11 / d;
	Result(1,0) = c12 / d;
	Result(2,0) = c13 / d;
	Result(3,0) = c14 / d;
	Result(0,1) = -((matrix.a32 * (matrix.a43 * matrix.a14 - matrix.a13 * matrix.a44)) - (matrix.a33 * (matrix.a42 * matrix.a14 - matrix.a12 * matrix.a44)) + (matrix.a34 * (matrix.a42 * matrix.a13 - matrix.a12 * matrix.a43))) / d;
	Result(1,1) =  ((matrix.a33 * (matrix.a44 * matrix.a11 - matrix.a14 * matrix.a41)) - (matrix.a34 * (matrix.a43 * matrix.a11 - matrix.a13 * matrix.a41)) + (matrix.a31 * (matrix.a43 * matrix.a14 - matrix.a13 * matrix.a44))) / d;
	Result(2,1) = -((matrix.a34 * (matrix.a41 * matrix.a12 - matrix.a11 * matrix.a42)) - (matrix.a31 * (matrix.a44 * matrix.a12 - matrix.a14 * matrix.a42)) + (matrix.a32 * (matrix.a44 * matrix.a11 - matrix.a14 * matrix.a41))) / d;
	Result(3,1) =  ((matrix.a31 * (matrix.a42 * matrix.a13 - matrix.a12 * matrix.a43)) - (matrix.a32 * (matrix.a41 * matrix.a13 - matrix.a11 * matrix.a43)) + (matrix.a33 * (matrix.a41 * matrix.a12 - matrix.a11 * matrix.a42))) / d;
	Result(0,2) =  ((matrix.a42 * (matrix.a13 * matrix.a24 - matrix.a23 * matrix.a14)) - (matrix.a43 * (matrix.a12 * matrix.a24 - matrix.a22 * matrix.a14)) + (matrix.a44 * (matrix.a12 * matrix.a23 - matrix.a22 * matrix.a13))) / d;
	Result(1,2) = -((matrix.a43 * (matrix.a14 * matrix.a21 - matrix.a24 * matrix.a11)) - (matrix.a44 * (matrix.a13 * matrix.a21 - matrix.a23 * matrix.a11)) + (matrix.a41 * (matrix.a13 * matrix.a24 - matrix.a23 * matrix.a14))) / d;
	Result(2,2) =  ((matrix.a44 * (matrix.a11 * matrix.a22 - matrix.a21 * matrix.a12)) - (matrix.a41 * (matrix.a14 * matrix.a22 - matrix.a24 * matrix.a12)) + (matrix.a42 * (matrix.a14 * matrix.a21 - matrix.a24 * matrix.a11))) / d;
	Result(3,2) = -((matrix.a41 * (matrix.a12 * matrix.a23 - matrix.a22 * matrix.a13)) - (matrix.a42 * (matrix.a11 * matrix.a23 - matrix.a21 * matrix.a13)) + (matrix.a43 * (matrix.a11 * matrix.a22 - matrix.a21 * matrix.a12))) / d;
	Result(0,3) = -((matrix.a12 * (matrix.a23 * matrix.a34 - matrix.a33 * matrix.a24)) - (matrix.a13 * (matrix.a22 * matrix.a34 - matrix.a32 * matrix.a24)) + (matrix.a14 * (matrix.a22 * matrix.a33 - matrix.a32 * matrix.a23))) / d;
	Result(1,3) =  ((matrix.a13 * (matrix.a24 * matrix.a31 - matrix.a34 * matrix.a21)) - (matrix.a14 * (matrix.a23 * matrix.a31 - matrix.a33 * matrix.a21)) + (matrix.a11 * (matrix.a23 * matrix.a34 - matrix.a33 * matrix.a24))) / d;
	Result(2,3) = -((matrix.a14 * (matrix.a21 * matrix.a32 - matrix.a31 * matrix.a22)) - (matrix.a11 * (matrix.a24 * matrix.a32 - matrix.a34 * matrix.a22)) + (matrix.a12 * (matrix.a24 * matrix.a31 - matrix.a34 * matrix.a21))) / d;
	Result(3,3) =  ((matrix.a11 * (matrix.a22 * matrix.a33 - matrix.a32 * matrix.a23)) - (matrix.a12 * (matrix.a21 * matrix.a33 - matrix.a31 * matrix.a23)) + (matrix.a13 * (matrix.a21 * matrix.a32 - matrix.a31 * matrix.a22))) / d;

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

std::ostream &operator<< (std::ostream &stream, const Matrix4 &mat)
{
	for (int y = 0; y < 4; ++y)
	{
		stream << "{";
		for (int x = 0; x < 4; ++x)
		{
			stream << mat(y,x);
			if (x != 3) stream << ",";
		}
		stream << "}";
		if (y != 3) stream << std::endl;
	}
	return stream;
}

}}