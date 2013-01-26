#include "Shader.h"
#include "GLHeader.h"

using namespace std;

namespace Tocs {
namespace Graphics {

Shader::Shader(void)
	: ID (glCreateProgram ()),
	  _Linked (false)
{
	//Bind ();
	//UnBind ();
}

Shader::Shader (Shader &&moveme)
	: ID (moveme.ID),
	  _Linked (moveme._Linked),
	  UniformsByLocation(std::move(moveme.UniformsByLocation)),
	  UniformsByName(std::move(moveme.UniformsByName))
{
	moveme.ID = 0;
	moveme._Linked = false;
}

Shader::~Shader(void)
{
	glDeleteProgram (ID);
}

void Shader::AddCode (const ShaderCode &code)
{
	glAttachShader (ID,code.GetID ());
	GLErrorCheck ();
}

void Shader::Link ()
{
	//link
	glLinkProgram (ID);

	int result = 0;
	//Check if it linked
	glGetObjectParameterivARB (ID, GL_LINK_STATUS, &result);
	GLErrorCheck ();
	if (!result)
		return;

	//Check if its valid
	glGetObjectParameterivARB (ID, GL_VALIDATE_STATUS, &result);
	GLErrorCheck ();
	if (!result)
		return;

	int uniformcount = 0;
	glGetObjectParameterivARB (ID, GL_OBJECT_ACTIVE_UNIFORMS_ARB, &uniformcount);
	GLErrorCheck ();
	//Build uniform table
	char tempname [500];
	int namelen = 0;
	int size = 0;
	GLenum type;
	int TextureRegister = 0;

	for (int i = 0; i < uniformcount; ++i)
	{
		memset (tempname,0,500);
		glGetActiveUniform (ID,i,500,&namelen,&size,&type,tempname);
		GLErrorCheck ();
		ShaderUniform *uniform = nullptr;
		if (type == GL_SAMPLER_2D || type == GL_SAMPLER_2D_ARRAY || type == GL_SAMPLER_3D)
		{
			uniform = new ShaderUniform (tempname,glGetUniformLocation (ID,tempname),TextureRegister);
			++TextureRegister;
		}
		else
		{
			uniform = new ShaderUniform (tempname,glGetUniformLocation (ID,tempname));
		}

		UniformsByName[uniform->GetName ()] = uniform;
		UniformsByLocation[uniform->GetLocation ()] = uniform;
	}
}

ShaderUniform &Shader::operator [] (string name)
{
	return *UniformsByName [name];
}
ShaderUniform &Shader::operator [] (int address)
{
	return *UniformsByLocation [address];
}

void Shader::Bind ()
{
	glUseProgram (ID);
	GLErrorCheck ();
}

void Shader::UnBind ()
{
	glUseProgram(0);
	GLErrorCheck ();
}

string Shader::GetLinkErrors ()
{
	int loglen;
	glGetProgramiv(ID,GL_INFO_LOG_LENGTH,&loglen);
	GLErrorCheck ();
	if (loglen == 0)
		return "No Errors.";

	string result;
	int resultlen;
	result.resize (loglen);
	glGetProgramInfoLog (ID,loglen,&resultlen,&result[0]);
	GLErrorCheck ();
	return result;
}

void Shader::SetAttribute (std::string attribute, int index)
{
	glBindAttribLocation (ID,index,attribute.c_str ());
	GLErrorCheck ();
}
int Shader::GetAttribute (std::string attribute) const
{
	return glGetAttribLocation (ID,attribute.c_str ());
}
int Shader::GetOutput (std::string output) const
{
	return glGetFragDataLocation (ID,output.c_str ());
}
void Shader::SetOutput (std::string output, int index)
{
	glBindFragDataLocation (ID,index,output.c_str ());
	GLErrorCheck ();
}

}}