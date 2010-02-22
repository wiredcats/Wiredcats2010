#ifndef KICKER_H_
#define KICKER_H_

#include "WPILib.h"
#include "CAN/CANJaguar.h"

const UINT32 ENCODER_CHANNEL_1 = 4;
const UINT32 ENCODER_CHANNEL_2 = 5;

const int SPIKE_NUM = 3;

//Distances Encoder need to go from 0.
const int LOW_GEAR_DIST = 100;
const int MID_GEAR_DIST = 200;
const int HIGH_GEAR_DIST = 300; 

class Kicker {
public:
	Encoder *encoder;
	Relay winch;
	Compressor *compressor;
	//Solenoid *dogsolenoid;
	Solenoid *firesolenoid;
	Servo *servo;
	
	bool backdriveEnabled;
	
	
	
	typedef enum { kWinchUp, kWinchStop } KickerSetting;
	
	Kicker();
	void ResetEncoder();
	float GetEncoder();
	
	void StartCompressor();
	
	void EngageFireSolenoid();
	void DisengageFireSolenoid();
	
	void SetServo();
	void ReleaseFireSolenoid();
	
	void RunBackdrive();
	
	void MoveKicker(KickerSetting ks);
	
	void GoToLowGear();
	void GoToMidGear();
	void GoToHighGear();
	
	void KickBall();
}; 

#endif
