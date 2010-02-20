#ifndef ARM_H_
#define ARM_H_

#include <WPILib.h>
#include "CAN/CANJaguar.h"

const float WINCH_MOTOR_SPEED = 0.6;

class Arm {
public:
	typedef enum { wUp, wDown, wStop } WinchFunction;
	typedef enum { sRelease, sLock } ServoSetting;
	
	CANJaguar *rWinch;
	CANJaguar *lWinch;
	Servo *dogServo;
	
	Arm();
	
	// Winch functions
	void RunWinch(WinchFunction wf);
	void SetServo(ServoSetting ss);
};

#endif
