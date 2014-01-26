#include "App.h"
#include "NativeIncludes.h"
#include "Window.h"
namespace Tocs {
namespace Ui {

void App::PumpMessages()
{
	MSG msg;
	BOOL bRet;

	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			// handle the error and possibly exit
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}


OSHandle App::GetDummyWindow()
{
	static Window Dummy ("Dummy", Size(100, 100));
	return Dummy.GetHandle();
}

}}