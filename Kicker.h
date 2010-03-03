#ifndef KICKER_H_
#define KICKER_H_

#include "WPILib.h"
#include "CAN/CANJaguar.h"

const int SPIKE_NUM = 3;

class Kicker {
public:
	Relay winch;
	Compressor *compressor;
	Solenoid *firesolenoid;
	Servo *servo;
	
	bool backdriveEnabled;
	
	typedef enum { kWinchUp, kWinchStop } KickerSetting;
	
	Kicker();
	
	void StartCompressor();

	void MoveKicker(KickerSetting ks);
	
	bool BackdriveEnabled();
	
	void UnlockServo();
	void LockServo();
	
	void EngageFireSolenoid();
	void DisengageFireSolenoid();

	void RunBackdrive();
	void StopBackdrive();
}; 

#endif
