#include "WPILib.h"

class Gamepad {
public:
	Joystick *stick;
	
	Gamepad(UINT32 port);
	bool buttonOnePressed();
};
