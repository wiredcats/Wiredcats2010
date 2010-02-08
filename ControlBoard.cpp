#include "ControlBoard.h"

ControlBoard::ControlBoard() {
	leftStick = new Joystick(RIGHT_JOY_PORT);
	rightStick = new Joystick(LEFT_JOY_PORT);
	fakeStick = new Joystick(FAKE_JOY_PORT);
	
	ds = DriverStation::GetInstance();
}


// Joysticks
Joystick* ControlBoard::GetLeftJoy() {
	return leftStick;
}

Joystick* ControlBoard::GetRightJoy() {
	return rightStick;
}

Joystick* ControlBoard::GetFakeJoy() {
	return fakeStick;
}


// Levers
bool LeftLeverUp() {
	return fakeStick->GetRawButton(LEFT_LEV_UP_PORT);
}

bool LeftLeverDown() {
	return fakeStick->GetRawButton(LEFT_LEV_DOWN_PORT);
}

bool MiddleLeverUp() {
	return fakeStick->GetRawButton(MID_LEV_UP_PORT);
}

bool MiddleLeverDown() {
	return fakeStick->GetRawButton(MID_LEV_DOWN_PORT);
}

bool RightLeverUp() {
	return fakeStick->GetRawButton(RIGHT_LEV_UP_PORT);
}

bool RightLeverDown() {
	return fakeStick->GetRawButton(RIGHT_LEV_DOWN_PORT);
}


// Buttons
bool LowWinchDown() {
	return fakeStick->GetRawButton(LOW_WINCH_BUTTON_PORT);
}

bool MidWinchDown() {
	return fakeStick->GetRawButton(MID_WINCH_BUTTON_PORT);
}

bool HighWinchDown() {
	return fakeStick->GetRawButton(HIGH_WINCH_BUTTON_PORT);
}

bool ServeBallDown() {
	return fakeStick->GetRawButton(SERVE_BALL_BUTTON_PORT);
}


// Light LEDs
void LightLowWinchLED() {
	ds->SetDigitalOut(LOW_WINCH_LED_PORT);
}

void LightMidWinchLED() {
	ds->SetDigitalOut(MID_WINCH_LED_PORT);
}

void LightHighWinchLED() {
	ds->SetDigitalOut(HIGH_WINCH_LED_PORT);
}


// Are LEDs lit?
bool LowWinchLEDLit() {
	return ds->GetDigitalOut(LOW_WINCH_LED_PORT);
}

bool MidWinchLEDLit() {
	return ds->GetDigitalOut(MID_WINCH_LED_PORT);
}

bool HighWinchLEDLit() {
	return ds->GetDigitalOut(HIGH_WINCH_LED_PORT);
}

