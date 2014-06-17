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
const ShaderVariableType ShaderVariableType::Sampler1DArrayShadow(GL_SAMPLER_1D_ARRAY_SHADOW);
const ShaderVariableType ShaderVariableType::Sampler2DArrayShadow(GL_SAMPLER_2D_ARRAY_SHADOW);
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
const ShaderVariableType ShaderVariableType::ShaderStorage(GL_SHADER_STORAGE_BLOCK);

#define ToStringMacro(Name, Constant) case Constant: return #Name

string ShaderVariableType::ToString () const
{
	switch (Internal)
	{
		ToStringMacro(Float, GL_FLOAT);
		ToStringMacro(Vector2, GL_FLOAT_VEC2);
		ToStringMacro(Vector3, GL_FLOAT_VEC3);
		ToStringMacro(Vector4, GL_FLOAT_VEC4);
		ToStringMacro(Double, GL_DOUBLE);
		ToStringMacro(DVector2, GL_DOUBLE_VEC2);
		ToStringMacro(DVector3, GL_DOUBLE_VEC3);
		ToStringMacro(DVector4, GL_DOUBLE_VEC4);
		ToStringMacro(Int, GL_INT);
		ToStringMacro(IVector2, GL_INT_VEC2);
		ToStringMacro(IVector3, GL_INT_VEC3);
		ToStringMacro(IVector4, GL_INT_VEC4);
		ToStringMacro(UnsignedInt, GL_UNSIGNED_INT);
		ToStringMacro(UIVector2, GL_UNSIGNED_INT_VEC2);
		ToStringMacro(UIVector3, GL_UNSIGNED_INT_VEC3);
		ToStringMacro(UIVector4, GL_UNSIGNED_INT_VEC4);
		ToStringMacro(Boolean, GL_BOOL);
		ToStringMacro(BVector2, GL_BOOL_VEC2);
		ToStringMacro(BVector3, GL_BOOL_VEC3);
		ToStringMacro(BVector4, GL_BOOL_VEC4);
		ToStringMacro(Matrix, GL_FLOAT_MAT4);
		ToStringMacro(Sampler1D, GL_SAMPLER_1D);
		ToStringMacro(Sampler2D, GL_SAMPLER_2D);
		ToStringMacro(Sampler3D, GL_SAMPLER_3D);
		ToStringMacro(SamplerCube, GL_SAMPLER_CUBE);
		ToStringMacro(Sampler1DShadow, GL_SAMPLER_1D_SHADOW);
		ToStringMacro(Sampler2DShadow, GL_SAMPLER_2D_SHADOW);
		ToStringMacro(Sampler1DArray, GL_SAMPLER_1D_ARRAY);
		ToStringMacro(Sampler2DArray, GL_SAMPLER_2D_ARRAY);
		ToStringMacro(Sampler1DArrayShadow, GL_SAMPLER_1D_ARRAY_SHADOW);
		ToStringMacro(Sampler2DArrayShadow, GL_SAMPLER_2D_ARRAY_SHADOW);
		ToStringMacro(SamplerCubeArrayShadow, GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW);
		ToStringMacro(Sampler2DMultiSample, GL_SAMPLER_2D_MULTISAMPLE);
		ToStringMacro(Sampler2DMultiSampleArray, GL_SAMPLER_2D_MULTISAMPLE_ARRAY);
		ToStringMacro(SamplerCubeShadow, GL_SAMPLER_CUBE_SHADOW);
		ToStringMacro(SamplerBuffer, GL_SAMPLER_BUFFER);
		ToStringMacro(Sampler2DRect, GL_SAMPLER_2D_RECT);
		ToStringMacro(Sampler2DRectShadow, GL_SAMPLER_2D_RECT_SHADOW);
		ToStringMacro(IntSampler1D, GL_INT_SAMPLER_1D);
		ToStringMacro(IntSampler2D, GL_INT_SAMPLER_2D);
		ToStringMacro(IntSampler3D, GL_INT_SAMPLER_3D);
		ToStringMacro(IntSamplerCube, GL_INT_SAMPLER_CUBE);
		ToStringMacro(IntSampler1DArray, GL_INT_SAMPLER_1D_ARRAY);
		ToStringMacro(IntSampler2DArray, GL_INT_SAMPLER_2D_ARRAY);
		ToStringMacro(IntSampler2DMultiSample, GL_INT_SAMPLER_2D_MULTISAMPLE);
		ToStringMacro(IntSampler2DMultiSampleArray, GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY);
		ToStringMacro(IntSamplerBuffer, GL_INT_SAMPLER_BUFFER);
		ToStringMacro(IntSampler2DRect, GL_INT_SAMPLER_2D_RECT);
		ToStringMacro(UIntSampler1D, GL_UNSIGNED_INT_SAMPLER_1D);
		ToStringMacro(UIntSampler2D, GL_UNSIGNED_INT_SAMPLER_2D);
		ToStringMacro(UIntSampler3D, GL_UNSIGNED_INT_SAMPLER_3D);
		ToStringMacro(UIntSamplerCube, GL_UNSIGNED_INT_SAMPLER_CUBE);
		ToStringMacro(UIntSampler1DArray, GL_UNSIGNED_INT_SAMPLER_1D_ARRAY);
		ToStringMacro(UIntSampler2DArray, GL_UNSIGNED_INT_SAMPLER_2D_ARRAY);
		ToStringMacro(UIntSampler2DMultiSample, GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE);
		ToStringMacro(UIntSampler2DMultiSampleArray, GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY);
		ToStringMacro(UIntSamplerBuffer, GL_UNSIGNED_INT_SAMPLER_BUFFER);
		ToStringMacro(UIntSampler2DRect, GL_UNSIGNED_INT_SAMPLER_2D_RECT);
		ToStringMacro(Image1D, GL_IMAGE_1D);
		ToStringMacro(Image2D, GL_IMAGE_2D);
		ToStringMacro(Image3D, GL_IMAGE_3D);
		ToStringMacro(Image2DRect, GL_IMAGE_2D_RECT);
		ToStringMacro(ImageCube, GL_IMAGE_CUBE);
		ToStringMacro(ImageBuffer, GL_IMAGE_BUFFER);
		ToStringMacro(Image1DArray, GL_IMAGE_1D_ARRAY);
		ToStringMacro(Image2DArray, GL_IMAGE_2D_ARRAY);
		ToStringMacro(Image2DMultiSample, GL_IMAGE_2D_MULTISAMPLE);
		ToStringMacro(Image2DMultiSampleArray, GL_IMAGE_2D_MULTISAMPLE_ARRAY);
		ToStringMacro(IntImage1D, GL_INT_IMAGE_1D);
		ToStringMacro(IntImage2D, GL_INT_IMAGE_2D);
		ToStringMacro(IntImage3D, GL_INT_IMAGE_3D);
		ToStringMacro(IntImage2DRect, GL_INT_IMAGE_2D_RECT);
		ToStringMacro(IntImageCube, GL_INT_IMAGE_CUBE);
		ToStringMacro(IntImageBuffer, GL_INT_IMAGE_BUFFER);
		ToStringMacro(IntImage1DArray, GL_INT_IMAGE_1D_ARRAY);
		ToStringMacro(IntImage2DArray, GL_INT_IMAGE_2D_ARRAY);
		ToStringMacro(IntImage2DMultiSample, GL_INT_IMAGE_2D_MULTISAMPLE);
		ToStringMacro(IntImage2DMultiSampleArray, GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY);
		ToStringMacro(UIntImage1D, GL_UNSIGNED_INT_IMAGE_1D);
		ToStringMacro(UIntImage2D, GL_UNSIGNED_INT_IMAGE_2D);
		ToStringMacro(UIntImage3D, GL_UNSIGNED_INT_IMAGE_3D);
		ToStringMacro(UIntImage2DRect, GL_UNSIGNED_INT_IMAGE_2D_RECT);
		ToStringMacro(UIntImageCube, GL_UNSIGNED_INT_IMAGE_CUBE);
		ToStringMacro(UIntImageBuffer, GL_UNSIGNED_INT_IMAGE_BUFFER);
		ToStringMacro(UIntImage1DArray, GL_UNSIGNED_INT_IMAGE_1D_ARRAY);
		ToStringMacro(UIntImage2DArray, GL_UNSIGNED_INT_IMAGE_2D_ARRAY);
		ToStringMacro(UIntImage2DMultiSample, GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE);
		ToStringMacro(UIntImage2DMultiSampleArray, GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY);
		ToStringMacro(Block, GL_UNIFORM_BLOCK);
		ToStringMacro(ShaderStorage, GL_SHADER_STORAGE_BLOCK);
	}
	return "ERROR";
}

unsigned int ShaderVariableType::SizeInBytes() const
{
	switch (Internal)
	{
	case GL_FLOAT:
		return sizeof(float);
	case GL_FLOAT_VEC2:
		return 2 * sizeof(float);
	case GL_FLOAT_VEC3:
		return 3 * sizeof(float);
	case GL_FLOAT_VEC4:
		return 4 * sizeof(float);
	case GL_DOUBLE:
		return sizeof(double);
	case GL_DOUBLE_VEC2:
		return 2*sizeof(double);
	case GL_DOUBLE_VEC3:
		return 3 * sizeof(double);
	case GL_DOUBLE_VEC4:
		return 4 * sizeof(double);
	case GL_INT:
		return sizeof(int);
	case GL_INT_VEC2:
		return 2 * sizeof(int);
	case GL_INT_VEC3:
		return 3 * sizeof(int);
	case GL_INT_VEC4:
		return 4 * sizeof(int);
	case GL_UNSIGNED_INT:
		return sizeof(unsigned int);
	case GL_UNSIGNED_INT_VEC2:
		return 2 * sizeof(unsigned int);
	case GL_UNSIGNED_INT_VEC3:
		return 3 * sizeof(unsigned int);
	case GL_UNSIGNED_INT_VEC4:
		return 4 * sizeof(unsigned int);
	case GL_BOOL:
		return sizeof(bool);
	case GL_BOOL_VEC2:
		return 2 * sizeof(bool);
	case GL_BOOL_VEC3:
		return 3 * sizeof(bool);
	case GL_BOOL_VEC4:
		return 4 * sizeof(bool);
	case GL_FLOAT_MAT4:
		return 16 * sizeof(float);
	}
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
	case GL_DOUBLE:
		return "double";
	case GL_DOUBLE_VEC2:
		return "dvec2";
	case GL_DOUBLE_VEC3:
		return "dvec3";
	case GL_DOUBLE_VEC4:
		return "dvec4";
	case GL_INT:
		return "int";
	case GL_INT_VEC2:
		return "ivec2";
	case GL_INT_VEC3:
		return "ivec3";
	case GL_INT_VEC4:
		return "ivec4";
	case GL_UNSIGNED_INT:
		return "unsigned int";
	case GL_UNSIGNED_INT_VEC2:
		return "uvec2";
	case GL_UNSIGNED_INT_VEC3:
		return "uvec3";
	case GL_UNSIGNED_INT_VEC4:
		return "uvec4";
	case GL_BOOL:
		return "bool";
	case GL_BOOL_VEC2:
		return "bvec2";
	case GL_BOOL_VEC3:
		return "bvec3";
	case GL_BOOL_VEC4:
		return "bvec4";
	case GL_FLOAT_MAT4:
		return "mat4";
	case GL_FLOAT_MAT2x4:
		return "mat2x4";
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

bool ShaderVariableType::IsBuffer() const
{
	return Internal == GL_UNIFORM_BLOCK
		|| Internal == GL_SHADER_STORAGE_BLOCK;
}


const ShaderType ShaderType::Vertex(vertex);
const ShaderType ShaderType::Pixel(pixel);
const ShaderType ShaderType::Geometry(geometry);
const ShaderType ShaderType::Compute(compute);

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
	case GL_COMPUTE_SHADER:
		return Compute;
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
	case compute:
		return GL_COMPUTE_SHADER;
	}
}


}}