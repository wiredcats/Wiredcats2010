#include "Kicker.h" 

Kicker::Kicker() {
	servo = new Servo(SERVO_PORT);
}

void Kicker::disengageServo() {
	servo->SetAngle(0.8);
}

void Kicker::engageServo() {
	servo->SetAngle(0.2);
}
