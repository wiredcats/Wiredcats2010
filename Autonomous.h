#ifndef AUTONOMOUS_H_
#define AUTONOMOUS_H_

//Libraries (Do we have too many? Ah well.)
#include "WPILib.h"
#include "PIDController.h"
#include "CAN/CANJaguar.h"
#include "Vision/AxisCamera.h"
#include "Vision/HSLImage.h"
#include "Target.h"

// Constants
const float VOLTAGE_DROP = 1.4;
const float BALL_SPACING_WAIT_TIME = 1.0;
const double ANGLE_THRESHOLD = 5.0;

//Copy Pasta Constants from Wiredcats2010.h
#define PROPORTION 0.1
#define INTEGRAL 0.0
#define DERIVATIVE 0.5
#define MINIMUM_SCORE 0.01
#define AUTO_THRESHOLD 4

//Drive PID class
class DrivePID : public PIDOutput
{
public:
	DrivePID (RobotDrive *base) {
		m_base = base;
	}
	
	void PIDWrite(float output) {
		m_base->ArcadeDrive(0.0, output);
	}
private:
	RobotDrive *m_base;
};

//Autonomous Controller Class
class AutoController {
public:
	AutoController (RobotDrive *drive, Gyro *gyro, CANJaguar *jaguar);
	RobotDrive *a_base;
	Gyro *a_gyro;
	CANJaguar *a_jag;
	PIDOutput *a_PIDOutput;
	PIDController *a_turnController;
	HSLImage image;
	AxisCamera *camera;
	
	//Go To Ball #
	void GoToBallOne();
	void GoToBallTwo();
	void GoToBallThree();
	void GoToBallFour();
	void GoToBallFive();
	void GoToBallSix();
	void GoToBallSeven();
	void GoToBallEight();
	void GoToBallNine();
	
	//Turn Compass Direction
	void TurnNorth();
	void TurnNorthEast();
	void TurnEast();
	void TurnSouthEast();
	void TurnSouth();
	void TurnSouthWest();
	void TurnWest();
	void TurnNorthWest();
	
	//Turn to Targets
	//Note: These are identical to TurnEast and TurnWest
	//		with some autotracking built in.
	void TurnToOurTarget();
	void TurnToEnemyTarget();
	
	//Check Robot Info
	bool IsTracked();
	bool HasBall(float initJagVoltage);
	void Orientation();
}; 

#endif
