#include "ShaderTypes.h"
#include "GLHeader.h"
using namespace std;
namespace Tocs {
namespace Graphics {

const ShaderVariableType ShaderVariableType::Float(GL_FLOAT);
const ShaderVariableType ShaderVariableType::Vector2(GL_FLOAT_VEC2);
const ShaderVariableType ShaderVariableType::Vector3(GL_FLOAT_VEC3);
const ShaderVariableType ShaderVariableType::Vector4(GL_FLOAT_VEC4);
const ShaderVariableType ShaderVariableType::Double(GL_DOUBLE);
const ShaderVariableType ShaderVariableType::DVector2(GL_DOUBLE_VEC2);
const ShaderVariableType ShaderVariableType::DVector3(GL_DOUBLE_VEC3);
const ShaderVariableType ShaderVariableType::DVector4(GL_DOUBLE_VEC4);
const ShaderVariableType ShaderVariableType::Int(GL_INT);
const ShaderVariableType ShaderVariableType::IVector2(GL_INT_VEC2);
const ShaderVariableType ShaderVariableType::IVector3(GL_INT_VEC3);
const ShaderVariableType ShaderVariableType::IVector4(GL_INT_VEC4);
const ShaderVariableType ShaderVariableType::UnsignedInt(GL_UNSIGNED_INT);
const ShaderVariableType ShaderVariableType::UIVector2(GL_UNSIGNED_INT_VEC2);
const ShaderVariableType ShaderVariableType::UIVector3(GL_UNSIGNED_INT_VEC3);
const ShaderVariableType ShaderVariableType::UIVector4(GL_UNSIGNED_INT_VEC4);
const ShaderVariableType ShaderVariableType::Boolean(GL_BOOL);
const ShaderVariableType ShaderVariableType::BVector2(GL_BOOL_VEC2);
const ShaderVariableType ShaderVariableType::BVector3(GL_BOOL_VEC3);
const ShaderVariableType ShaderVariableType::BVector4(GL_BOOL_VEC4);
const ShaderVariableType ShaderVariableType::Matrix(GL_FLOAT_MAT4);

const ShaderVariableType ShaderVariableType::Sampler1D(GL_SAMPLER_1D);
const ShaderVariableType ShaderVariableType::Sampler2D(GL_SAMPLER_2D);
const ShaderVariableType ShaderVariableType::Sampler3D(GL_SAMPLER_3D);
const ShaderVariableType ShaderVariableType::SamplerCube(GL_SAMPLER_CUBE);
const ShaderVariableType ShaderVariableType::Sampler1DShadow(GL_SAMPLER_1D_SHADOW);
const ShaderVariableType ShaderVariableType::Sampler2DShadow(GL_SAMPLER_2D_SHADOW);
const ShaderVariableType ShaderVariableType::Sampler1DArray(GL_SAMPLER_1D_ARRAY);
const ShaderVariableType ShaderVariableType::Sampler2DArray(GL_SAMPLER_2D_ARRAY);
const ShaderVariableType ShaderVariableType::Sampler1DArrayShadow(GL_SAMPLER_1D_SHADOW);
const ShaderVariableType ShaderVariableType::Sampler2DArrayShadow(GL_SAMPLER_2D_SHADOW);
const ShaderVariableType ShaderVariableType::SamplerCubeArrayShadow(GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW);
const ShaderVariableType ShaderVariableType::Sampler2DMultiSample(GL_SAMPLER_2D_MULTISAMPLE);
const ShaderVariableType ShaderVariableType::Sampler2DMultiSampleArray(GL_SAMPLER_2D_MULTISAMPLE_ARRAY);
const ShaderVariableType ShaderVariableType::SamplerCubeShadow(GL_SAMPLER_CUBE_SHADOW);
const ShaderVariableType ShaderVariableType::SamplerBuffer(GL_SAMPLER_BUFFER);
const ShaderVariableType ShaderVariableType::Sampler2DRect(GL_SAMPLER_2D_RECT);
const ShaderVariableType ShaderVariableType::Sampler2DRectShadow(GL_SAMPLER_2D_RECT_SHADOW);

const ShaderVariableType ShaderVariableType::IntSampler1D(GL_INT_SAMPLER_1D);
const ShaderVariableType ShaderVariableType::IntSampler2D(GL_INT_SAMPLER_2D);
const ShaderVariableType ShaderVariableType::IntSampler3D(GL_INT_SAMPLER_3D);
const ShaderVariableType ShaderVariableType::IntSamplerCube(GL_INT_SAMPLER_CUBE);
const ShaderVariableType ShaderVariableType::IntSampler1DArray(GL_INT_SAMPLER_1D_ARRAY);
const ShaderVariableType ShaderVariableType::IntSampler2DArray(GL_INT_SAMPLER_2D_ARRAY);
const ShaderVariableType ShaderVariableType::IntSampler2DMultiSample(GL_INT_SAMPLER_2D_MULTISAMPLE);
const ShaderVariableType ShaderVariableType::IntSampler2DMultiSampleArray(GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY);
const ShaderVariableType ShaderVariableType::IntSamplerBuffer(GL_INT_SAMPLER_BUFFER);
const ShaderVariableType ShaderVariableType::IntSampler2DRect(GL_INT_SAMPLER_2D_RECT);

const ShaderVariableType ShaderVariableType::UIntSampler1D(GL_UNSIGNED_INT_SAMPLER_1D);
const ShaderVariableType ShaderVariableType::UIntSampler2D(GL_UNSIGNED_INT_SAMPLER_2D);
const ShaderVariableType ShaderVariableType::UIntSampler3D(GL_UNSIGNED_INT_SAMPLER_3D);
const ShaderVariableType ShaderVariableType::UIntSamplerCube(GL_UNSIGNED_INT_SAMPLER_CUBE);
const ShaderVariableType ShaderVariableType::UIntSampler1DArray(GL_UNSIGNED_INT_SAMPLER_1D_ARRAY);
const ShaderVariableType ShaderVariableType::UIntSampler2DArray(GL_UNSIGNED_INT_SAMPLER_2D_ARRAY);
const ShaderVariableType ShaderVariableType::UIntSampler2DMultiSample(GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE);
const ShaderVariableType ShaderVariableType::UIntSampler2DMultiSampleArray(GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY);
const ShaderVariableType ShaderVariableType::UIntSamplerBuffer(GL_UNSIGNED_INT_SAMPLER_BUFFER);
const ShaderVariableType ShaderVariableType::UIntSampler2DRect(GL_UNSIGNED_INT_SAMPLER_2D_RECT);

const ShaderVariableType ShaderVariableType::Image1D(GL_IMAGE_1D);
const ShaderVariableType ShaderVariableType::Image2D(GL_IMAGE_2D);
const ShaderVariableType ShaderVariableType::Image3D(GL_IMAGE_3D);
const ShaderVariableType ShaderVariableType::Image2DRect(GL_IMAGE_2D_RECT);
const ShaderVariableType ShaderVariableType::ImageCube(GL_IMAGE_CUBE);
const ShaderVariableType ShaderVariableType::ImageBuffer(GL_IMAGE_BUFFER);
const ShaderVariableType ShaderVariableType::Image1DArray(GL_IMAGE_1D_ARRAY);
const ShaderVariableType ShaderVariableType::Image2DArray(GL_IMAGE_2D_ARRAY);
const ShaderVariableType ShaderVariableType::Image2DMultiSample(GL_IMAGE_2D_MULTISAMPLE);
const ShaderVariableType ShaderVariableType::Image2DMultiSampleArray(GL_IMAGE_2D_MULTISAMPLE_ARRAY);

const ShaderVariableType ShaderVariableType::IntImage1D(GL_INT_IMAGE_1D);
const ShaderVariableType ShaderVariableType::IntImage2D(GL_INT_IMAGE_2D);
const ShaderVariableType ShaderVariableType::IntImage3D(GL_INT_IMAGE_3D);
const ShaderVariableType ShaderVariableType::IntImage2DRect(GL_INT_IMAGE_2D_RECT);
const ShaderVariableType ShaderVariableType::IntImageCube(GL_INT_IMAGE_CUBE);
const ShaderVariableType ShaderVariableType::IntImageBuffer(GL_INT_IMAGE_BUFFER);
const ShaderVariableType ShaderVariableType::IntImage1DArray(GL_INT_IMAGE_1D_ARRAY);
const ShaderVariableType ShaderVariableType::IntImage2DArray(GL_INT_IMAGE_2D_ARRAY);
const ShaderVariableType ShaderVariableType::IntImage2DMultiSample(GL_INT_IMAGE_2D_MULTISAMPLE);
const ShaderVariableType ShaderVariableType::IntImage2DMultiSampleArray(GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY);

const ShaderVariableType ShaderVariableType::UIntImage1D(GL_UNSIGNED_INT_IMAGE_1D);
const ShaderVariableType ShaderVariableType::UIntImage2D(GL_UNSIGNED_INT_IMAGE_2D);
const ShaderVariableType ShaderVariableType::UIntImage3D(GL_UNSIGNED_INT_IMAGE_3D);
const ShaderVariableType ShaderVariableType::UIntImage2DRect(GL_UNSIGNED_INT_IMAGE_2D_RECT);
const ShaderVariableType ShaderVariableType::UIntImageCube(GL_UNSIGNED_INT_IMAGE_CUBE);
const ShaderVariableType ShaderVariableType::UIntImageBuffer(GL_UNSIGNED_INT_IMAGE_BUFFER);
const ShaderVariableType ShaderVariableType::UIntImage1DArray(GL_UNSIGNED_INT_IMAGE_1D_ARRAY);
const ShaderVariableType ShaderVariableType::UIntImage2DArray(GL_UNSIGNED_INT_IMAGE_2D_ARRAY);
const ShaderVariableType ShaderVariableType::UIntImage2DMultiSample(GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE);
const ShaderVariableType ShaderVariableType::UIntImage2DMultiSampleArray(GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY);

const ShaderVariableType ShaderVariableType::Block(GL_UNIFORM_BLOCK);

string ShaderVariableType::ToString () const
{
	switch (Internal)
	{
	case GL_FLOAT:
		return "Float";
	case GL_FLOAT_VEC2:
		return "Vector2";
	case GL_FLOAT_VEC3:
		return "Vector3";
	case GL_FLOAT_VEC4:
		return "Vector4";
	case GL_FLOAT_MAT4:
		return "Matrix";
	case GL_INT:
		return "Int";
	}
	return "ERROR";
}
string ShaderVariableType::ToGLSLTypeString () const
{
	switch (Internal)
	{
	case GL_FLOAT:
		return "float";
	case GL_FLOAT_VEC2:
		return "vec2";
	case GL_FLOAT_VEC3:
		return "vec3";
	case GL_FLOAT_VEC4:
		return "vec4";
	case GL_FLOAT_MAT4:
		return "mat4";
	case GL_INT:
		return "int";
	}
	return "ERROR";
}


const ShaderVariableType &ShaderVariableType::FromGLSLTypeString (const std::string &type)
{
	if (type == "vec2")
		return Vector2;
	if (type == "vec3")
		return Vector3;
	if (type == "vec4")
		return Vector4;
	if (type == "mat4")
		return Matrix;
	if (type == "int")
		return Int;
	if (type == "float")
		return Float;
	return Int;
}

unsigned int ShaderVariableType::VectorComponents () const
{
	switch (Internal)
	{
	case GL_FLOAT_VEC2:
		return 2;
	case GL_FLOAT_VEC3:
		return 3;
	case GL_FLOAT_VEC4:
		return 4;
	case GL_INT:
		return 1;
	case GL_FLOAT:
		return 1;
	}
	return 0;
}

std::string ShaderVariableType::GetTruncationSwizzle (const ShaderVariableType &from, const ShaderVariableType &to)
{
	static char Swizzle[4] = {'x','y','z','w'};
	int fcnt = from.VectorComponents ();
	int tcnt = to.VectorComponents ();

	if (fcnt < tcnt)
		return "";
	if (fcnt == 1)
		return "";
	return std::string (&Swizzle[0],&Swizzle[tcnt]);
}

ShaderVariableType ShaderVariableType::FromGLUniformType (int type)
{
	return ShaderVariableType(type); //Check the value?
}

bool ShaderVariableType::IsSampler() const
{
	return Internal == GL_SAMPLER_1D
		|| Internal == GL_SAMPLER_2D
		|| Internal == GL_SAMPLER_3D
		|| Internal == GL_SAMPLER_CUBE
		|| Internal == GL_SAMPLER_1D_SHADOW
		|| Internal == GL_SAMPLER_2D_SHADOW
		|| Internal == GL_SAMPLER_1D_ARRAY
		|| Internal == GL_SAMPLER_2D_ARRAY
		|| Internal == GL_SAMPLER_1D_ARRAY_SHADOW
		|| Internal == GL_SAMPLER_2D_ARRAY_SHADOW
		|| Internal == GL_SAMPLER_2D_MULTISAMPLE
		|| Internal == GL_SAMPLER_2D_MULTISAMPLE_ARRAY
		|| Internal == GL_SAMPLER_CUBE_SHADOW
		|| Internal == GL_SAMPLER_BUFFER
		|| Internal == GL_SAMPLER_2D_RECT
		|| Internal == GL_SAMPLER_2D_RECT_SHADOW
		|| Internal == GL_INT_SAMPLER_1D
		|| Internal == GL_INT_SAMPLER_2D
		|| Internal == GL_INT_SAMPLER_3D
		|| Internal == GL_INT_SAMPLER_CUBE
		|| Internal == GL_INT_SAMPLER_1D_ARRAY
		|| Internal == GL_INT_SAMPLER_2D_ARRAY
		|| Internal == GL_INT_SAMPLER_2D_MULTISAMPLE
		|| Internal == GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY
		|| Internal == GL_INT_SAMPLER_BUFFER
		|| Internal == GL_INT_SAMPLER_2D_RECT
		|| Internal == GL_UNSIGNED_INT_SAMPLER_1D
		|| Internal == GL_UNSIGNED_INT_SAMPLER_2D
		|| Internal == GL_UNSIGNED_INT_SAMPLER_3D
		|| Internal == GL_UNSIGNED_INT_SAMPLER_CUBE
		|| Internal == GL_UNSIGNED_INT_SAMPLER_1D_ARRAY
		|| Internal == GL_UNSIGNED_INT_SAMPLER_2D_ARRAY
		|| Internal == GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE
		|| Internal == GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY
		|| Internal == GL_UNSIGNED_INT_SAMPLER_BUFFER
		|| Internal == GL_UNSIGNED_INT_SAMPLER_2D_RECT
		|| Internal == GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW;
}

bool ShaderVariableType::IsImage() const
{
	return Internal == GL_INT_SAMPLER_1D
		|| Internal == GL_INT_SAMPLER_2D
		|| Internal == GL_INT_SAMPLER_3D
		|| Internal == GL_INT_SAMPLER_CUBE
		|| Internal == GL_INT_SAMPLER_1D_ARRAY
		|| Internal == GL_INT_SAMPLER_2D_ARRAY
		|| Internal == GL_INT_SAMPLER_2D_MULTISAMPLE
		|| Internal == GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY
		|| Internal == GL_INT_SAMPLER_BUFFER
		|| Internal == GL_INT_SAMPLER_2D_RECT
		|| Internal == GL_IMAGE_1D
		|| Internal == GL_IMAGE_2D
		|| Internal == GL_IMAGE_3D
		|| Internal == GL_IMAGE_2D_RECT
		|| Internal == GL_IMAGE_CUBE
		|| Internal == GL_IMAGE_BUFFER
		|| Internal == GL_IMAGE_1D_ARRAY
		|| Internal == GL_IMAGE_2D_ARRAY
		|| Internal == GL_IMAGE_2D_MULTISAMPLE
		|| Internal == GL_IMAGE_2D_MULTISAMPLE_ARRAY
		|| Internal == GL_INT_IMAGE_1D
		|| Internal == GL_INT_IMAGE_2D
		|| Internal == GL_INT_IMAGE_3D
		|| Internal == GL_INT_IMAGE_2D_RECT
		|| Internal == GL_INT_IMAGE_CUBE
		|| Internal == GL_INT_IMAGE_BUFFER
		|| Internal == GL_INT_IMAGE_1D_ARRAY
		|| Internal == GL_INT_IMAGE_2D_ARRAY
		|| Internal == GL_INT_IMAGE_2D_MULTISAMPLE
		|| Internal == GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY
		|| Internal == GL_UNSIGNED_INT_IMAGE_1D
		|| Internal == GL_UNSIGNED_INT_IMAGE_2D
		|| Internal == GL_UNSIGNED_INT_IMAGE_3D
		|| Internal == GL_UNSIGNED_INT_IMAGE_2D_RECT
		|| Internal == GL_UNSIGNED_INT_IMAGE_CUBE
		|| Internal == GL_UNSIGNED_INT_IMAGE_BUFFER
		|| Internal == GL_UNSIGNED_INT_IMAGE_1D_ARRAY
		|| Internal == GL_UNSIGNED_INT_IMAGE_2D_ARRAY
		|| Internal == GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE
		|| Internal == GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY;
}


const ShaderType ShaderType::Vertex(vertex);
const ShaderType ShaderType::Pixel(pixel);
const ShaderType ShaderType::Geometry(geometry);

ShaderType ShaderType::FromGLType (unsigned int gltype)
{
	switch (gltype)
	{
	case GL_VERTEX_SHADER:
		return Vertex;
	case GL_FRAGMENT_SHADER:
		return Pixel;
	case GL_GEOMETRY_SHADER:
		return Geometry;
	}
}

unsigned int ShaderType::GetGLType () const
{
	switch (Internal)
	{
	case vertex:
		return GL_VERTEX_SHADER;
	case pixel:
		return GL_FRAGMENT_SHADER;
	case geometry:
		return GL_GEOMETRY_SHADER;
	}
}


}}