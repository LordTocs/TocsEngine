#pragma once
#include "Key.h"
namespace Tocs {
namespace Input {

class Keyboard
{
	float KeyTimes [256];
public:
	friend class SimpleWindow;

	Keyboard();

	void Update (float dt);
	bool IsPressed (const Key &key);
	bool IsNewlyPressed (const Key &key);
	bool IsRepeatedlyPressed (const Key &key);

};

}}
