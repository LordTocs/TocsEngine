#include "GraphicsContext.h"
#include "GLHeader.h"
#include <iostream>

using namespace std;

using namespace Tocs::Math;

namespace Tocs {
namespace Graphics {

static void APIENTRY dbgcallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, void* userParam)
{
	std::cout << "Debug(";

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:
		std::cout << "api";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		std::cout << "win";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		std::cout << "shdcomp";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		std::cout << "app";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		std::cout << "other";
		break;
	}

	std::cout << ", ";

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		std::cout << "h";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		std::cout << "m";
		break;
	case GL_DEBUG_SEVERITY_LOW:
		std::cout << "l";
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		std::cout << "n";
		break;
	}

	std::cout << "): ";

	std::cout << "[" << id << "] ";

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:
		std::cout << "ERROR - ";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		std::cout << "DEPRICATED - ";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		std::cout << "UNDEFINED - ";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		std::cout << "PORTABILITY - ";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		std::cout << "PERFORMANCE - ";
		break;
	case GL_DEBUG_TYPE_MARKER:
		std::cout << "MARKER - ";
		break;
	case GL_DEBUG_TYPE_PUSH_GROUP:
		std::cout << "PUSH - ";
		break;
	case GL_DEBUG_TYPE_POP_GROUP:
		std::cout << "POP - ";
		break;
	case GL_DEBUG_TYPE_OTHER:
		std::cout << "OTHER - ";
		break;
	}

	std::cout << message << std::endl;
}

GraphicsContext::GraphicsContext(ContextTarget &target)
	: Target (target)
{
	PIXELFORMATDESCRIPTOR pfd=			// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// Size Of This Pixel Format Descriptor
		1,								// Version Number
		PFD_DRAW_TO_WINDOW |			// Format Must Support Window
		PFD_SUPPORT_OPENGL |			// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,				// Must Support Double Buffering
		PFD_TYPE_RGBA,					// Request An RGBA Format
		32,								// Select Our Color Depth
		0, 0, 0, 0, 0, 0,				// Color Bits Ignored
		0,								// No Alpha Buffer
		0,								// Shift Bit Ignored
		0,								// No Accumulation Buffer
		0, 0, 0, 0,						// Accumulation Bits Ignored
		32,								// 32Bit Z-Buffer (Depth Buffer)
		0,								// No Stencil Buffer
		0,								// No Auxiliary Buffer
		PFD_MAIN_PLANE,					// Main Drawing Layer
		0,								// Reserved
		0, 0, 0								// Layer Masks Ignored
	};

	if (!(PixelFormat = ChoosePixelFormat (target.GetHDC (), &pfd)))
	{
		cout << "Failed to choose pixel format." << endl;
	}

	if (!SetPixelFormat(target.GetHDC(),PixelFormat, &pfd))
	{
		//DestroyGameWindow (); //Insert Error
		cout << "Failed to set pixel format." << endl;
	}

	HGLRC temp;
	if (!(temp = wglCreateContext (target.GetHDC ())))
	{
		//DestroyGameWindow (); //Insert Error
		cout << "Failed to create context" << endl;
	}

	if (!wglMakeCurrent(target.GetHDC (), temp))
	{
		//DestroyGameWindow (); 
		cout << "Failed to make current." << endl;
	}

	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		char *error = (char *)glewGetErrorString(err);
		cout << "GLEW INIT FAIL: " << error << endl;
	}

	int attribs [] = 
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 2,
		WGL_CONTEXT_FLAGS_ARB, 
#ifdef _DEBUG
		WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB | WGL_CONTEXT_DEBUG_BIT_ARB,
#else
		WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
#endif
		0
	};

	if (wglewIsSupported ("WGL_ARB_create_context") == 1)
	{
		if (!(hRC = (wglCreateContextAttribsARB(Target.GetHDC(), 0, attribs))))
		{
			std::cout << "Failed to create context." << std::endl;
		}
		GLErrorCheck();
		MakeCurrent ();
		wglDeleteContext (temp);
		wglMakeCurrent (Target.GetHDC (),hRC);
	}
	else
	{
		cout << "Failed to create context again..." << endl;
	}

#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(dbgcallback, nullptr);
#endif


	char *shadeversion = (char *)glGetString (GL_SHADING_LANGUAGE_VERSION);
	//GLErrorCheck;
	char *version = (char *)glGetString(GL_VERSION);
	//GLErrorCheck;
	std::cout << "Version: " << version << std::endl << "Shading Version: " << shadeversion << std::endl;

	glViewport (0,0,Target.GetWidth (), Target.GetHeight ());
	GLErrorCheck ();


	SetClearColor (Color(0,0,0,0));
	SetClearDepth(1000.0f);
	//EnableDepthBuffering ();
	//DisableDepthTest ();
	NormalBlending ();

	

	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST); //Doesn't get Abstracted
	GLErrorCheck();



	//glLoadIdentity ();
}


GraphicsContext::~GraphicsContext(void)
{
	wglDeleteContext (hRC);
}

void GraphicsContext::MakeCurrent ()
{
	wglMakeCurrent (Target.GetHDC (),hRC);
	GLErrorCheck ();
}
bool GraphicsContext::HasExtension (std::string extension)
{
	return false;
}

void GraphicsContext::AlphaBlending ()
{
	glEnable (GL_BLEND);
	GLErrorCheck();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GLErrorCheck();
}
void GraphicsContext::NormalBlending ()
{
	glDisable(GL_BLEND);
	GLErrorCheck ();
}
void GraphicsContext::AdditiveBlending ()
{
	glEnable (GL_BLEND);
	GLErrorCheck ();
	glBlendFunc (GL_ONE,GL_ONE);
	GLErrorCheck ();
}

void GraphicsContext::EnableDepthTest ()
{
	glEnable(GL_DEPTH_TEST);
	GLErrorCheck ();
	glDepthFunc (GL_LEQUAL);
	GLErrorCheck ();
}
void GraphicsContext::DisableDepthTest ()
{
	glDisable (GL_DEPTH_TEST);
	GLErrorCheck ();
}

void GraphicsContext::DisableDepthWrite()
{
	glDepthMask (false);
	GLErrorCheck ();
}

void GraphicsContext::EnableDepthWrite ()
{
	glDepthMask (true);
	GLErrorCheck ();
}

void GraphicsContext::SetClearColor (Color color)
{
	glClearColor (color.R/(255.0f),color.G/(255.0f),color.B/(255.0f),color.A/(255.0f));
	GLErrorCheck ();
}

void GraphicsContext::ClearActiveBuffer ()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	GLErrorCheck ();
}

void GraphicsContext::ClearColor ()
{
	glClear (GL_COLOR_BUFFER_BIT);
	GLErrorCheck ();
}

void GraphicsContext::ClearDepth ()
{
	glClear (GL_DEPTH_BUFFER_BIT);
	GLErrorCheck ();
}

void GraphicsContext::SetClearDepth (float depth)
{
	glClearDepth (depth);
	GLErrorCheck();
}

void GraphicsContext::FlipToScreen ()
{
	SwapBuffers(Target.GetHDC ());
	GLErrorCheck ();
}

void GraphicsContext::DrawTriangles (int triangles)
{
	glDrawElements (GL_TRIANGLES, triangles*3, GL_UNSIGNED_SHORT, nullptr);
	GLErrorCheck ();
}

void GraphicsContext::DrawTriangles (int offset, int length)
{
	glDrawElements (GL_TRIANGLES, length*3, GL_UNSIGNED_SHORT, reinterpret_cast<GLvoid*>(sizeof(unsigned short)*offset*3));
	GLErrorCheck ();
}

void GraphicsContext::DrawTriangles (int offset, int length, const IndexFormat &format)
{
	glDrawElements (GL_TRIANGLES, length*3, format.GetGLEnum (), reinterpret_cast<GLvoid*>(format.SizeInBytes()*offset*3));
	GLErrorCheck ();
}

void GraphicsContext::DrawTrianglesInstanced(int offset, int length,unsigned int instances, const IndexFormat &format)
{
	glDrawElementsInstanced(GL_TRIANGLES, length * 3, format.GetGLEnum(), reinterpret_cast<GLvoid*>(format.SizeInBytes()*offset * 3),instances);
	GLErrorCheck();
}

void GraphicsContext::DrawLines(int lines)
{
	glDrawElements(GL_LINES, lines * 2, GL_UNSIGNED_INT, nullptr);
	GLErrorCheck();
}

void GraphicsContext::EnableWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	GLErrorCheck ();
}

void GraphicsContext::DisableWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	GLErrorCheck ();
}

void GraphicsContext::EnableBackfaceCulling()
{
	glEnable(GL_CULL_FACE);
	GLErrorCheck ();
}

void GraphicsContext::DisableBackfaceCulling()
{
	glDisable(GL_CULL_FACE);
	GLErrorCheck ();
}

void GraphicsContext::AtomicCounterMemoryBarrier()
{
	glMemoryBarrier(GL_ATOMIC_COUNTER_BARRIER_BIT);
	GLErrorCheck();
}

void GraphicsContext::Viewport(unsigned int width, unsigned int height)
{
	glViewport(0, 0, width, height);
	GLErrorCheck();
}


void GraphicsContext::Compute(unsigned int groups)
{
	glDispatchCompute(groups, 1, 1);
	GLErrorCheck();
}
void GraphicsContext::Compute(unsigned int gwidth, unsigned int gheight)
{
	glDispatchCompute(gwidth, gheight, 1);
	GLErrorCheck();
}
void GraphicsContext::Compute(unsigned int gwidth, unsigned int gheight, unsigned int gdepth)
{
	glDispatchCompute(gwidth, gheight, gdepth);
	GLErrorCheck();
}

}}