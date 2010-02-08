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
bool ControlBoard::LeftLeverUp() {
	return fakeStick->GetRawButton(LEFT_LEV_UP_PORT);
}

bool ControlBoard::LeftLeverDown() {
	return fakeStick->GetRawButton(LEFT_LEV_DOWN_PORT);
}

bool ControlBoard::MiddleLeverUp() {
	return fakeStick->GetRawButton(MID_LEV_UP_PORT);
}

bool ControlBoard::MiddleLeverDown() {
	return fakeStick->GetRawButton(MID_LEV_DOWN_PORT);
}

bool ControlBoard::RightLeverUp() {
	return fakeStick->GetRawButton(RIGHT_LEV_UP_PORT);
}

bool ControlBoard::RightLeverDown() {
	return fakeStick->GetRawButton(RIGHT_LEV_DOWN_PORT);
}


// Buttons
bool ControlBoard::LowWinchDown() {
	return fakeStick->GetRawButton(LOW_WINCH_BUTTON_PORT);
}

bool ControlBoard::MidWinchDown() {
	return fakeStick->GetRawButton(MID_WINCH_BUTTON_PORT);
}

bool ControlBoard::HighWinchDown() {
	return fakeStick->GetRawButton(HIGH_WINCH_BUTTON_PORT);
}

bool ControlBoard::ServeBallDown() {
	return fakeStick->GetRawButton(SERVE_BALL_BUTTON_PORT);
}


// Light LEDs
void ControlBoard::LightLowWinchLED() {
	ds->SetDigitalOut(LOW_WINCH_LED_PORT,true);
}

void ControlBoard::LightMidWinchLED() {
	ds->SetDigitalOut(MID_WINCH_LED_PORT,true);
}

void ControlBoard::LightHighWinchLED() {
	ds->SetDigitalOut(HIGH_WINCH_LED_PORT,true);
}

//Turn Off LEDs
void ControlBoard::TurnOffLowWinchLED() {
	ds->SetDigitalOut(LOW_WINCH_LED_PORT,false);
}

void ControlBoard::TurnOffMidWinchLED() {
	ds->SetDigitalOut(MID_WINCH_LED_PORT,false);
}

void ControlBoard::TurnOffHighWinchLED() {
	ds->SetDigitalOut(HIGH_WINCH_LED_PORT,false);
}

// Are LEDs lit?
bool ControlBoard::LowWinchLEDLit() {
	return ds->GetDigitalOut(LOW_WINCH_LED_PORT);
}

bool ControlBoard::MidWinchLEDLit() {
	return ds->GetDigitalOut(MID_WINCH_LED_PORT);
}

bool ControlBoard::HighWinchLEDLit() {
	return ds->GetDigitalOut(HIGH_WINCH_LED_PORT);
}

