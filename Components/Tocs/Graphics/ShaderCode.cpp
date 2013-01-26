#include "ShaderCode.h"
#include "GLHeader.h"
#include <fstream>

using namespace std;

namespace Tocs {
namespace Graphics {

ShaderCode::ShaderCode(ShaderType type)
	: ID (glCreateShader (type.GetGLType ()))
{
	GLErrorCheck ();
}

ShaderCode::ShaderCode(ShaderCode && copyme)
	: ID (copyme.ID)
{
	copyme.ID = 0;
}


ShaderCode::~ShaderCode(void)
{
	glDeleteShader (ID);
	GLErrorCheck ();
}

bool ShaderCode::Compiled () const
{
	int result;
	glGetShaderiv (ID,GL_COMPILE_STATUS,&result);
	GLErrorCheck ();
	return (result != 0);
}

std::string ShaderCode::GetCompileErrors ()
{
	int loglen;
	glGetShaderiv (ID,GL_INFO_LOG_LENGTH,&loglen);
	GLErrorCheck ();
	if (loglen == 0)
		return "No Errors.";

	string result;
	int resultlen;
	result.resize (loglen);
	glGetShaderInfoLog (ID,loglen,&resultlen,&result[0]);
	GLErrorCheck ();
	return result;
}

void ShaderCode::Compile (const std::string &code)
{
	const char *codecstr = code.c_str ();
	glShaderSource (ID,1,&codecstr,nullptr);
	GLErrorCheck ();
	glCompileShader (ID);
	GLErrorCheck ();
}

void ShaderCode::CompileFromFile (const std::string &file)
{
	std::ifstream t(file);
	std::string str;

	t.seekg(0, std::ios::end);   
	str.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),
				std::istreambuf_iterator<char>());
	
	Compile(str);
}

ShaderType ShaderCode::GetType ()
{
	int result;
	glGetShaderiv (ID,GL_SHADER_TYPE,&result);
	GLErrorCheck ();
	return ShaderType::FromGLType (result);
}

}}