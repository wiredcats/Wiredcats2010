#include "Kicker.h" 

Kicker::Kicker() {
	distanceSetting = 2;
	servo = new Servo(SERVO_PORT);
	winch = new CANJaguar(WINCH_PORT);
}

void Kicker::DisengageServo() {
	servo->SetAngle(0.8);
	winched = false;
}

void Kicker::EngageServo() {
	servo->SetAngle(0.2);
}

void Kicker::SetDistance(int newd) {
	distanceSetting = newd;
}

void Kicker::WinchBack() {
	// do winch code
	winched = true;
}

bool Kicker::IsWinched() {
	return winched;
}