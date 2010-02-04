#ifndef KICKER_H_
#define KICKER_H_

#include "WPILib.h"

class Kicker {
public:
	Servo* servo;
	Kicker();
	void disengageServo();
	void EngageServo ();
}; 
#endif
