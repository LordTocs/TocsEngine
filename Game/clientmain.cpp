#include <iostream>
#include <utility>
#include <Tocs/Core/PackedFreeList.h>
#include "Game.h"
#include <Tocs/Graphics/GraphicsContext.h>
#include <Tocs/Input/SimpleWindow.h>
#include <Tocs/Core/Ticker.h>
#include <Tocs/Core/StackTrace.h>
#include <Tocs/Math/Vector.h>
#include <Tocs/Rendering/Material.h>



using namespace Tocs;
using namespace Tocs::Math;
using namespace Tocs::Rendering;
using namespace std;


int main ()
{
	cout << endl;
	Game game;
	game.Start();
}