#include "ControlBoard.h"

ControlBoard::ControlBoard() {
	leftStick = new Joystick(RIGHT_JOY_PORT);
	rightStick = new Joystick(LEFT_JOY_PORT);
}

Joystick* ControlBoard::GetLeftJoy() {
	return leftStick;
}

Joystick* ControlBoard::GetRightJoy() {
	return rightStick;
}
