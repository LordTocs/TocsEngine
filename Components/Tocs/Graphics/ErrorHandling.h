#pragma once
#include <string>
#include <iostream>
#include <Tocs/Core/StackTrace.h>
namespace Tocs {
namespace Graphics {

#define CHECK_OPENGL

#ifdef _DEBUG 
#ifdef CHECK_OPENGL
#define GLErrorCheck() if (Tocs::Graphics::ErrorCheck ()) { std::cout << "@: " << std::endl; Tocs::StackTrace().PrettyPrint(); }
#else
#define GLErrorCheck()
#endif
#else
#define GLErrorCheck()
#endif



bool ErrorCheck ();

}}
