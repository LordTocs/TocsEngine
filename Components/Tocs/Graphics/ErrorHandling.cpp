#include "ErrorHandling.h"
#include "GLHeader.h"
#include <iostream>

using namespace std;

namespace Tocs {
namespace Graphics {

//void HandleError (int error, const std::string &line, const std::string &file)
//cout << "\t@:" << file << "(" << line << ")" << endl;
bool ErrorCheck ()
{
	GLenum error = glGetError ();
	if (error != GL_NO_ERROR)
	{
		cout << "OpenGL error detected: " << endl;
		cout << "\tErr: ";
		switch (error)
		{
		case GL_INVALID_ENUM:
			cout << "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			cout << "GL_INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			cout << "GL_INVALID_OPERATION";
			break;
		case GL_STACK_UNDERFLOW:
			cout << "GL_STACK_UNDERFLOW";
			break;
		case GL_STACK_OVERFLOW:
			cout << "GL_STACK_OVERFLOW";
			break;
		case GL_OUT_OF_MEMORY:
			cout << "GL_OUT_OF_MEMORY";
			break;
		default:
			cout << "Something Else("<<error<<")";
		}
		cout << endl;
		return true;
	}
	return false;
}

}}