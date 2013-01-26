#pragma once

//#define TOCS_DLL

#ifdef TOCS_DLL
	#ifdef TOCSLIB
		#define TocsAPI __declspec(dllexport)
	#else
		#define TocsAPI __declspec(dllimport)
	#endif
#else
#define TocsAPI
#endif
