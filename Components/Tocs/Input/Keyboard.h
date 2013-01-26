#pragma once

namespace Tocs {
namespace Input {

class Keyboard
{
	float KeyTimes [256];
public:
	Keyboard(void);
	~Keyboard(void);

	void Update (float dt);
	bool IsPressed (int key);
	bool IsNewlyPressed (int key);
	bool IsRepeatedlyPressed (int key);

};

}}
