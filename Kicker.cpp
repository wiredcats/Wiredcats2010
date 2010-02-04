#include "Kicker.h" 

Kicker::Kicker() {
	distanceSetting = 2;
	servo = new Servo(4);
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
	// do winch code
}