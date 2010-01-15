#ifndef GAMEPAD_H_
#define GAMEPAD_H_

#include "WPILib.h"

class Gamepad {
public:
	Joystick *stick;
	
	Gamepad(UINT32 port);
	bool buttonOnePressed();
};

#endif
