#pragma once
#include "NativeHelpers.h"
namespace Tocs {
namespace Ui{

class App
{
public:
	App() = delete;
	App(const App &) = delete;
	App &operator= (const App &) = delete;

	static void PumpMessages();
	static OSHandle GetDummyWindow();
};

}}