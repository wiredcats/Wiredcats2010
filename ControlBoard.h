#ifndef CONTROLSTATION_H_
#define CONTROLSTATION_H_

#include "WPILib.h"

// Constants
const UINT32 RIGHT_JOY_PORT = 1;
const UINT32 LEFT_JOY_PORT = 2;

class ControlBoard {
public:
	Joystick *leftStick, *rightStick;
	
	ControlBoard();
	
	Joystick* GetLeftJoy();
	Joystick* GetRightJoy();
};

#endif
