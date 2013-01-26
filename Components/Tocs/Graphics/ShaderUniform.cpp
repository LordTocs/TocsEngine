#include "ShaderUniform.h"
#include "GLHeader.h"

using namespace std;
using namespace Tocs::Math;

namespace Tocs {
namespace Graphics {

ShaderUniform::ShaderUniform(string name, unsigned int location)
	: Name (name),
	  Location (location),
	  TextureRegister (-1)
{
}

ShaderUniform::ShaderUniform(string name, unsigned int location, unsigned int texture)
	: Name(name),
	  Location(location),
	  TextureRegister(texture)
{
}

ShaderUniform &ShaderUniform::operator = (const int &op2) 
{
	glUniform1i (Location,op2);
	return *this;
}
ShaderUniform &ShaderUniform::operator = (const float &op2)
{
	glUniform1f (Location,op2);
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
	return *this;
}

ShaderUniform &ShaderUniform::operator = (const Matrix4 &op2)
{
	glUniformMatrix4fv (Location,1,false,op2.GetData ());
	return *this;
}

ShaderUniform &ShaderUniform::operator= (const Math::Color &op2)
{
	glUniform4i (Location,op2.R,op2.G,op2.G,op2.A);
	return *this;
}


}}