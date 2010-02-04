#ifndef KICKER_H_
#define KICKER_H_

#include "WPILib.h"

class Kicker {
public:
	Servo* servo;
	int distanceSetting;
	
	Kicker();
	void DisengageServo();
	void EngageServo();
	void SetDistance(int newd);
	void WinchBack();
}; 

#endif
