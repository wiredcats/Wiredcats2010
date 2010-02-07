#ifndef CONTROLSTATION_H_
#define CONTROLSTATION_H_

#include "WPILib.h"

// Constants
const UINT32 RIGHT_JOY_PORT = 1;
const UINT32 LEFT_JOY_PORT = 2;
const UINT32 ALL_BUTTONS_PORT = 3;

class ControlBoard {
public:
	Joystick *leftStick, *rightStick, *fakeButtonsStick;
	
	ControlBoard();
	
	Joystick* GetLeftJoy();
	Joystick* GetRightJoy();
	Joystick* GetServeBallButton();
	bool GetButton1();
	bool GetButton2();
	bool GetButton3();
	bool GetLever1Up();
	bool GetLever1Down();
	bool GetLever2Up();
	bool GetLever2Down();
	bool GetLever3Up();
	bool GetLever3Down();
};

#endif
