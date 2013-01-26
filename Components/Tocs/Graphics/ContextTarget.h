#pragma once
#include <Windows.h>
namespace Tocs {
namespace Graphics {

class ContextTarget
{
public:
	friend class GraphicsContext;

	ContextTarget() {}
	virtual ~ContextTarget() {}

#ifdef WIN32
	virtual HWND GetWindowHandle () = 0;
	virtual HDC GetHDC () = 0;
#endif

	virtual int GetWidth () const = 0;
	virtual int GetHeight () const = 0;
};

}}

