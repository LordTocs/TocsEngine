#include "ShaderUniform.h"
#include "GLHeader.h"
#include <iostream>
#include "Shader.h"

using namespace std;
using namespace Tocs::Math;

namespace Tocs {
namespace Graphics {

ShaderUniform ShaderUniform::Dummy (nullptr,"Dummy",-1,ShaderVariableType::Int);

ShaderUniform::ShaderUniform(Shader *owningshader, string name, unsigned int location, const ShaderVariableType &type)
	: Name (name),
	  Location (location),
	  TextureRegister (-1),
	  Type(type),
	  OwningShader(owningshader)
{
}

ShaderUniform::ShaderUniform(Shader *owningshader, string name, unsigned int location, const ShaderVariableType &type, unsigned int texture)
	: Name(name),
	  Location(location),
	  TextureRegister(texture),
	  Type(type),
	  OwningShader(owningshader)
{
}

ShaderUniform &ShaderUniform::operator = (const int &op2) 
{
	if (Location == -1)
	{
		cout << "Wrote to a Dummy Uniform" << endl;
		return *this;
	}

	glUniform1i (Location,op2);
	GLErrorCheck ();
	//cout << "Ui: " << Name << " : " << op2 << endl;
	return *this;
}
ShaderUniform &ShaderUniform::operator = (const float &op2)
{
	if (Location == -1)
	{
		cout << "Wrote to a Dummy Uniform" << endl;
		return *this;
	}

	glUniform1f (Location,op2);
	GLErrorCheck ();
	//cout << "Uf: " << Name << " : " << op2 << endl;
	return *this;

}
ShaderUniform &ShaderUniform::operator = (const Texture2D &op2)
{
	if (Location == -1)
	{
		cout << "Wrote to a Dummy Uniform" << endl;
		return *this;
	}

	glUniform1i (Location,TextureRegister);
	GLErrorCheck ();
	op2.Bind (TextureRegister);
	//cout << "U: " << Name << " : tex" << TextureRegister << endl;
	return *this;
}
ShaderUniform &ShaderUniform::operator = (const Texture3D &op2)
{
	if (Location == -1)
	{
		cout << "Wrote to a Dummy Uniform" << endl;
		return *this;
	}

	glUniform1i (Location,TextureRegister);
	GLErrorCheck ();
	op2.Bind (TextureRegister);
	//cout << "U: " << Name << " : tex" << TextureRegister << endl;
	return *this;
}

ShaderUniform &ShaderUniform::operator= (const BufferTexture &op2)
{
	if (Location == -1)
	{
		cout << "Wrote to a Dummy Uniform" << endl;
		return *this;
	}

	glUniform1i (Location,TextureRegister);
	GLErrorCheck ();
	op2.Bind (TextureRegister);
	//cout << "U: " << Name << " : tex" << TextureRegister << endl;
	return *this;
}


ShaderUniform &ShaderUniform::operator = (const Vector3 &op2)
{
	return BindVector3(&op2,1);
}

ShaderUniform &ShaderUniform::BindVector3 (const Math::Vector3 *vec, int count)
{
	if (Location == -1)
	{
		cout << "Wrote to a Dummy Uniform" << endl;
		return *this;
	}

	glUniform3fv(Location,count,reinterpret_cast<const float *>(vec));
	GLErrorCheck ();
	//cout << "U: " << Name << " : " << op2 << endl;
	return *this;
}

ShaderUniform &ShaderUniform::operator = (const Matrix4 &op2)
{
	if (Location == -1)
	{
		cout << "Wrote to a Dummy Uniform" << endl;
		return *this;
	}
	glUniformMatrix4fv (Location,1,false,op2.GetData ());
	GLErrorCheck ();
	//cout << "U: " << Name << " : " << endl << op2 << endl;
	return *this;
}

ShaderUniform &ShaderUniform::operator= (const Math::Color &op2)
{
	if (Location == -1)
	{
		cout << "Wrote to a Dummy Uniform" << endl;
		return *this;
	}
	//cout << "U: " << Name << " : (" << (int)op2.R << ", " << (int)op2.G << ", " << (int)op2.B << ")"  << endl;
	if (Type == ShaderVariableType::Vector4)
	{
		glUniform4f (Location,op2.R/255.0f,op2.G/255.0f,op2.B/255.0f,op2.A/255.0f);
		GLErrorCheck ();
	}
	else if (Type == ShaderVariableType::Vector3)
	{
		glUniform3f (Location,op2.R/255.0f,op2.G/255.0f,op2.B/255.0f);
		GLErrorCheck ();
	}
	return *this;
}

ShaderUniform &ShaderUniform::operator= (const BufferBase &op2)
{
	if (Location == -1)
	{
		cout << "Wrote to a Dummy Uniform" << endl;
		return *this;
	}

	if (Type != ShaderVariableType::Block)
	{
		cout << "Attempted to bind UBO to regular uniform" << std::endl;
		return *this;
	}

	glUniformBlockBinding (OwningShader->GetID (),Location,TextureRegister);
	GLErrorCheck();

	op2.BindTo (BufferTarget::Uniform, TextureRegister); 

	return *this;
}



}}