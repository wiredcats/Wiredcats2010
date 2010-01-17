#ifndef CONTROLSTATION_H_
#define CONTROLSTATION_H_

#include "WPILib.h"

class ControlStation {
public:
	Joystick leftStick,rightStick;
	
	Joystick GetLeftJoy();
	Joystick GetRightJoy();
	bool buttonOnePressed();
};

#endif
