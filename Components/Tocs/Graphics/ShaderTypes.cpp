#include "ShaderTypes.h"
#include "GLHeader.h"
using namespace std;
namespace Tocs {
namespace Graphics {

const ShaderVariableType ShaderVariableType::Float(float_);
const ShaderVariableType ShaderVariableType::Vector2(vec2);
const ShaderVariableType ShaderVariableType::Vector3(vec3);
const ShaderVariableType ShaderVariableType::Vector4(vec4);
const ShaderVariableType ShaderVariableType::Matrix(mat4);
const ShaderVariableType ShaderVariableType::Int(int_);

string ShaderVariableType::ToString () const
{
	switch (Internal)
	{
	case float_:
		return "Float";
	case vec2:
		return "Vector2";
	case vec3:
		return "Vector3";
	case vec4:
		return "Vector4";
	case mat4:
		return "Matrix";
	case int_:
		return "Int";
	}
	return "ERROR";
}
string ShaderVariableType::ToGLSLTypeString () const
{
	switch (Internal)
	{
	case float_:
		return "float";
	case vec2:
		return "vec2";
	case vec3:
		return "vec3";
	case vec4:
		return "vec4";
	case mat4:
		return "mat4";
	case int_:
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
	case vec2:
		return 2;
	case vec3:
		return 3;
	case vec4:
		return 4;
	case int_:
		return 1;
	case float_:
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