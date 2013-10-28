#include "Ticker.h"
#define NOMINMAX
#include <Windows.h>

namespace Tocs {

Ticker::Ticker(void)
	: StartTime (GetTickCount ())
{
}

float Ticker::GetTickTime ()
{
	unsigned int time = GetTickCount ();
	float result = (time - StartTime)/1000.0f;
	StartTime = time;
	return result;
}

}
