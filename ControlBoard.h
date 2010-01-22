#ifndef CONTROLSTATION_H_
#define CONTROLSTATION_H_

#include "WPILib.h"

// Constants
const UINT32 RIGHT_JOY_PORT = 1;
const UINT32 LEFT_JOY_PORT = 2;

const UINT32 TILT_UP_LIMIT_DIO = 1;
const UINT32 TILT_LOW_LIMIT_DIO = 2;
const UINT32 EXTEND_UP_LIMIT_DIO = 3;
const UINT32 EXTEND_LOW_LIMIT_DIO = 4;

class ControlBoard {
public:
	Joystick *leftStick, *rightStick;
	DriverStation *ds;
	
	ControlBoard();
	
	Joystick* GetLeftJoy();
	Joystick* GetRightJoy();
	
	bool TiltUpperLimitLit();
	bool TiltLowerLimitLit();
	bool ExtendUpperLimitLit();
	bool ExtendLowerLimitLit();
};

#endif
