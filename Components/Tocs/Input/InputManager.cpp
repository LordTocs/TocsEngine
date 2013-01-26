#include "InputManager.h"

namespace Tocs {
namespace Input {

void InputManager::Update (float dt)
{
	Mouse.Update ();
	Keyboard.Update (dt);
}

}}