#include "ControlBoard.h"

ControlBoard::ControlBoard() {
	leftStick = new Joystick(RIGHT_JOY_PORT);
	rightStick = new Joystick(LEFT_JOY_PORT);
	fakeButtonsStick = new Joystick(ALL_BUTTONS_PORT);
}

Joystick* ControlBoard::GetLeftJoy() {
	return leftStick;
}

Joystick* ControlBoard::GetRightJoy() {
	return rightStick;
}

bool ControlBoard::GetButton1() {
	return fakeButtonsStick->GetRawButton(5);
}

bool ControlBoard::GetButton2() {
	return fakeButtonsStick->GetRawButton(3);
}

bool ControlBoard::GetButton3() {
	return fakeButtonsStick->GetRawButton(1);
}

bool ControlBoard::GetLever1Up() {
	return fakeButtonsStick->GetRawButton(10);
}

bool ControlBoard::GetLever1Down() {
	return fakeButtonsStick->GetRawButton(11);
}

bool ControlBoard::GetLever2Up() {
	return fakeButtonsStick->GetRawButton(9);
}

bool ControlBoard::GetLever2Down() {
	return fakeButtonsStick->GetRawButton(8);
}

bool ControlBoard::GetLever3Up() {
	return fakeButtonsStick->GetRawButton(7);
}

bool ControlBoard::GetLever3Down() {
	return fakeButtonsStick->GetRawButton(6);
}
