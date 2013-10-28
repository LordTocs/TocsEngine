#pragma once
#include <string>
#include <iostream>
#include <Tocs/Core/StackTrace.h>
namespace Tocs {
namespace Graphics {

#ifdef _DEBUG 
#define GLErrorCheck() if (Tocs::Graphics::ErrorCheck ()) { std::cout << "@: " << std::endl; Tocs::StackTrace().PrettyPrint(); }
#else
#define GLErrorCheck()
#endif



bool ErrorCheck ();

}}
