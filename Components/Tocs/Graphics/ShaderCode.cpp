#include "ShaderCode.h"
#include "GLHeader.h"
#include <fstream>
#include <Tocs/Core/Error.h>
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

static void HandleInclude(std::string &shader)
{
	size_t start_pos = 0;
	std::string include_dir = "#include ";

	while ((start_pos = shader.find(include_dir, start_pos)) != std::string::npos)
	{
		int pos = start_pos + include_dir.length() + 1;
		int length = shader.find("\"", pos);
		std::string file = shader.substr(pos, length - pos);
		std::string content = "";

		std::ifstream f;
		f.open(file.c_str());

		if (f.is_open())
		{
			f.seekg(0, std::ios::end);
			content.reserve(f.tellg());
			f.seekg(0, std::ios::beg);

			content.assign((std::istreambuf_iterator<char>(f)),
			std::istreambuf_iterator<char>());
		}
		else
		{
			std::cerr << "Couldn't include shader file: " << std::endl;
		}

		HandleInclude(content);

		shader.replace(start_pos, (length + 1) - start_pos, content);
		start_pos += content.length();
	}
}

void ShaderCode::Compile (std::string code)
{
	HandleInclude(code);
	const char *codecstr = code.c_str ();
	glShaderSource (ID,1,&codecstr,nullptr);
	GLErrorCheck ();
	glCompileShader (ID);
	GLErrorCheck ();
}

void ShaderCode::CompileFromFile (const std::string &file)
{
	std::ifstream t;

	t.open (file.c_str ());

	if (!t.good ())
	{
		cout << "Unable to open " << file << endl;
		return;
	}
	

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

ShaderCode ShaderCode::LoadFromFile (const std::string &filename)
{
	ShaderType type = ShaderType::Vertex;
	if (filename.find(".frag") != string::npos)
		type = ShaderType::Pixel;
	if (filename.find(".geom") != string::npos)
		type = ShaderType::Geometry;
	if (filename.find(".comp") != string::npos)
		type = ShaderType::Compute;

	ShaderCode result (type);

	result.CompileFromFile (filename);

	if (!result.Compiled ())
	{
		cout << "Error compiling: " << filename << ": " << endl << result.GetCompileErrors () << endl;
		assert(false);
	}

	return std::move(result);
}

}}