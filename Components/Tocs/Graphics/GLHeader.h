#pragma once
#include <gl/glew.h>

#ifdef WIN32
#include <gl/wglew.h>
#define NOMINMAX
#include <windows.h>
#endif

#include <gl/GL.h>

#include "ErrorHandling.h"