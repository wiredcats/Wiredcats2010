#include "Kicker.h" 

Kicker::Kicker() {
	distanceSetting = 2;
	servo = new Servo(SERVO_PORT);
	winch = new CANJaguar(WINCH_PORT);
}

void Kicker::DisengageServo() {
	servo->SetAngle(0.8);
}

void Kicker::EngageServo() {
	servo->SetAngle(0.2);
}

void Kicker::SetDistance(int newd) {
	distanceSetting = newd;
}

void Kicker::WinchBack() {
	winch->Set(-0.6);
	Wait(3.0);
	winch->Set(0.0);
}

