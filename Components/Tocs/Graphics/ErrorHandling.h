#pragma once
#include <string>
#include <iostream>
namespace Tocs {
namespace Graphics {

#ifdef _DEBUG 
#define GLErrorCheck() if (Tocs::Graphics::ErrorCheck ()) { std::cout << "\t@:(" << __LINE__ << "): " << __FILE__  << std::endl; }
#else
#define GLErrorCheck()
#endif



bool ErrorCheck ();

}}
