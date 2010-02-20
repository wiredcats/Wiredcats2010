#ifndef ARM_H_
#define ARM_H_

#include <WPILib.h>
#include "CAN/CANJaguar.h"

const float WINCH_MOTOR_SPEED = 0.6;

class Arm {
public:
	typedef enum { wUp, wDown, wStop } WinchFunction;
	typedef enum { sRelease, sLock } ServoSetting;
	typedef enum { aRaise, aLower, aStill } ArmSetting;
	typedef enum { aExtend, aRetract, aStop} TelescopeSetting;
	
	CANJaguar *rWinch;
	CANJaguar *lWinch;
	Servo *dogServo;
	CANJaguar *runArm;
	Relay extendArm;
	
	Arm();
	
	// Winch functions
	void RunWinch(WinchFunction wf);
	void SetServo(ServoSetting ss);
	void MoveArm(ArmSetting as);
    void ExtendArm(TelescopeSetting ts);
};


#endif
