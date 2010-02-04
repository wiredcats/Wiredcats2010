#include "Kicker.h" 

Kicker::Kicker(){
	servo = new Servo(4);
}
void Kicker::disengageServo(){
	servo->SetAngle(0.8);
}
void Kicker::EngageServo(){
	servo->SetAngle(0.2);
}
