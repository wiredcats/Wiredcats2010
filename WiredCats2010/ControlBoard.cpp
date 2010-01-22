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

float ControlBoard::GetTiltValue() {
	return ds->GetAnalogIn(TILT_LEVER_PORT);
}

float ControlBoard::GetExtendValue() {
	return ds->GetAnalogIn(EXTEND_LEVER_PORT);
}

bool ControlBoard::Button1Lit() {
	return ds->GetDigitalOut(READY_BUTTON_1_DIO);
}

bool ControlBoard::Button2Lit() {
	return ds->GetDigitalOut(READY_BUTTON_2_DIO);
}

bool ControlBoard::Button3Lit() {
	return ds->GetDigitalOut(READY_BUTTON_3_DIO);
}

float ControlBoard::GetButton1() {
	return ds->GetAnalogIn(BUTTON_1_PORT);
}

float ControlBoard::GetButton2() {
	return ds->GetAnalogIn(BUTTON_2_PORT);
}

float ControlBoard::GetButton3() {
	return ds->GetAnalogIn(BUTTON_3_PORT);
}
