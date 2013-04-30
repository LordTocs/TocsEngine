#include "ShaderUniform.h"
#include "GLHeader.h"

using namespace std;
using namespace Tocs::Math;

namespace Tocs {
namespace Graphics {

ShaderUniform::ShaderUniform(string name, unsigned int location, const ShaderVariableType &type)
	: Name (name),
	  Location (location),
	  TextureRegister (-1),
	  Type(type)
{
}

ShaderUniform::ShaderUniform(string name, unsigned int location, const ShaderVariableType &type, unsigned int texture)
	: Name(name),
	  Location(location),
	  TextureRegister(texture),
	  Type(type)
{
}

ShaderUniform &ShaderUniform::operator = (const int &op2) 
{
	glUniform1i (Location,op2);
	GLErrorCheck ();
	return *this;
}
ShaderUniform &ShaderUniform::operator = (const float &op2)
{
	glUniform1f (Location,op2);
	GLErrorCheck ();
	return *this;

}
ShaderUniform &ShaderUniform::operator = (const Texture2D &op2)
{
	glUniform1i (Location,TextureRegister);
	GLErrorCheck ();
	op2.Bind (TextureRegister);
	return *this;
}
ShaderUniform &ShaderUniform::operator = (const Texture3D &op2)
{
	glUniform1i (Location,TextureRegister);
	GLErrorCheck ();
	op2.Bind (TextureRegister);
	return *this;
}

ShaderUniform &ShaderUniform::operator = (const Vector3 &op2)
{
	glUniform3f(Location, op2.X, op2.Y, op2.Z);
	GLErrorCheck ();
	return *this;
}

ShaderUniform &ShaderUniform::operator = (const Matrix4 &op2)
{
	glUniformMatrix4fv (Location,1,false,op2.GetData ());
	GLErrorCheck ();
	return *this;
}

ShaderUniform &ShaderUniform::operator= (const Math::Color &op2)
{
	if (Type == ShaderVariableType::Vector4)
	{
		glUniform4f (Location,op2.R/255.0f,op2.G/255.0f,op2.G/255.0f,op2.A/255.0f);
		GLErrorCheck ();
	}
	else if (Type == ShaderVariableType::Vector3)
	{
		glUniform3f (Location,op2.R/255.0f,op2.G/255.0f,op2.G/255.0f);
		GLErrorCheck ();
	}
	return *this;
}


}}