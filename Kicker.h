#ifndef KICKER_H_
#define KICKER_H_

#include "WPILib.h"
#include "CAN/CANJaguar.h"

const UINT32 SERVO_PORT = 4;
const UINT32 WINCH_PORT = 5;

class Kicker {
public:
	Servo* servo;
	Jaguar* winch;
	
	int distanceSetting;
	bool winched;
	
	Kicker();
	void DisengageServo();
	void EngageServo();
	void SetDistance(int newd);
	void WinchBack();
	bool IsWinched();
}; 

#endif
