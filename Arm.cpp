#include "Arm.h"

Arm::Arm() {
	rWinch = new CANJaguar(6);
	lWinch = new CANJaguar(8);
	dogServo = new Servo(1);
}

void Arm::RunWinch(Arm::WinchFunction wf) {
	switch (wf) {
	case wUp:
		rWinch->Set(WINCH_MOTOR_SPEED);
		lWinch->Set(WINCH_MOTOR_SPEED);
		break;
	case wDown:
		rWinch->Set(-WINCH_MOTOR_SPEED);
		lWinch->Set(-WINCH_MOTOR_SPEED);
		break;
	case wStop:
		rWinch->Set(0.0);
		lWinch->Set(0.0);
	default:
		// Uh oh...
		break;
	}
}

void Arm::SetServo(Arm::ServoSetting ss) {
	switch (ss) {
	case sLock:
		dogServo->Set(0.8);
		break;
	case sRelease:
		dogServo->Set(0.2);
		break;
	default:
		// Uh oh...
		break;
	}
}
