#include "GraphicsContext.h"
#include "GLHeader.h"
#include <iostream>

using namespace std;

using namespace Tocs::Math;

namespace Tocs {
namespace Graphics {

GraphicsContext::GraphicsContext(ContextTarget &target)
	: Target (target)
{
	PIXELFORMATDESCRIPTOR pfd=					// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),					// Size Of This Pixel Format Descriptor
		1,								// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,						// Must Support Double Buffering
		PFD_TYPE_RGBA,							// Request An RGBA Format
		32,								// Select Our Color Depth
		0, 0, 0, 0, 0, 0,						// Color Bits Ignored
		0,								// No Alpha Buffer
		0,								// Shift Bit Ignored
		0,								// No Accumulation Buffer
		0, 0, 0, 0,							// Accumulation Bits Ignored
		32,								// 16Bit Z-Buffer (Depth Buffer)
		0,								// No Stencil Buffer
		0,								// No Auxiliary Buffer
		PFD_MAIN_PLANE,							// Main Drawing Layer
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

	GLenum err = glewInit ();

	if (err != GLEW_OK)
	{
		char *error = (char *)glewGetErrorString(err);
		cout << "GLEW INIT FAIL: " << error << endl;
	}

	int attribs [] = 
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 1,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		0
	};

	if (wglewIsSupported ("WGL_ARB_create_context") == 1)
	{
		hRC = (wglCreateContextAttribsARB(Target.GetHDC (),0, attribs));
		MakeCurrent ();
		wglDeleteContext (temp);
		wglMakeCurrent (Target.GetHDC (),hRC);
	}
	else
	{
		cout << "Failed to create context again..." << endl;
	}

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
	DisableDepthBuffering ();
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
	glBlendFunc (GL_ALPHA,GL_ONE);
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

void GraphicsContext::EnableDepthBuffering ()
{
	glEnable(GL_DEPTH_TEST);
	GLErrorCheck ();
	glDepthFunc (GL_LEQUAL);
	GLErrorCheck ();
}
void GraphicsContext::DisableDepthBuffering ()
{
	glDisable (GL_DEPTH_TEST);
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
	glDrawRangeElements (GL_TRIANGLES, offset*3,(offset+length)*3,length*3, GL_UNSIGNED_SHORT, nullptr);
	GLErrorCheck ();
}

}}