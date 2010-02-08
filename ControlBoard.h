#ifndef CONTROLSTATION_H_
#define CONTROLSTATION_H_

#include "WPILib.h"

// Constants
const UINT32 RIGHT_JOY_PORT = 1;
const UINT32 LEFT_JOY_PORT = 2;
const UINT32 FAKE_JOY_PORT = 3;

const UINT32 LEFT_LEV_UP_PORT = 11;
const UINT32 LEFT_LEV_DOWN_PORT = 10;
const UINT32 MID_LEV_UP_PORT = 9;
const UINT32 MID_LEV_DOWN_PORT = 8;
const UINT32 RIGHT_LEV_UP_PORT = 7;
const UINT32 RIGHT_LEV_DOWN_PORT = 6;

const UINT32 LOW_WINCH_BUTTON_PORT = 5;
const UINT32 MID_WINCH_BUTTON_PORT = 3;
const UINT32 HIGH_WINCH_BUTTON_PORT = 1;
const UINT32 SERVE_BALL_BUTTON_PORT = 2;

const UINT32 LOW_WINCH_LED_PORT = 5;
const UINT32 MID_WINCH_LED_PORT = 3;
const UINT32 HIGH_WINCH_LED_PORT = 1;

class ControlBoard {
public:
	Joystick *leftStick, *rightStick, *fakeStick;
	DriverStation *ds;
	
	ControlBoard();
	
	Joystick* GetLeftJoy();
	Joystick* GetRightJoy();
	Joystick* GetFakeJoy();
	
	// Levers
	bool LeftLeverUp();
	bool LeftLeverDown();
	bool MiddleLeverUp();
	bool MiddleLeverDown();
	bool RightLeverUp();
	bool RightLeverDown();
	
	// Buttons
	bool LowWinchDown();
	bool MidWinchDown();
	bool HighWinchDown();
	bool ServeBallDown();
	
	// Light LEDs
	void LightLowWinchLED();
	void LightMidWinchLED();
	void LightHighWinchLED();
	
	// Are LEDs lit?
	bool LowWinchLEDLit();
	bool MidWinchLEDLit();
	bool HighWinchLEDLit();
};

#endif
