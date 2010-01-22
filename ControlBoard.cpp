#include "ControlBoard.h"

ControlBoard::ControlBoard() {
	leftStick = new Joystick(RIGHT_JOY_PORT);
	rightStick = new Joystick(LEFT_JOY_PORT);
	ds = DriverStation::GetInstance();
}

Joystick* ControlBoard::GetLeftJoy() {
	return leftStick;
}

Joystick* ControlBoard::GetRightJoy() {
	return rightStick;
}

bool ControlBoard::TiltUpperLimitLit() {
	return ds->GetDigitalOut(TILT_UP_LIMIT_DIO);
}

bool ControlBoard::TiltLowerLimitLit() {
	return ds->GetDigitalOut(TILT_LOW_LIMIT_DIO);
}

bool ControlBoard::ExtendUpperLimitLit() {
	return ds->GetDigitalOut(EXTEND_UP_LIMIT_DIO);
}

bool ControlBoard::ExtendLowerLimitLit() {
	return ds->GetDigitalOut(EXTEND_LOW_LIMIT_DIO);
}
