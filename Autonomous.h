#ifndef AUTONOMOUS_H_
#define AUTONOMOUS_H_

#include "WPILib.h"
#include "PIDController.h"

#define PROPORTION 0.1
#define INTEGRAL 0.0
#define DERIVATIVE 0.5

// Constants
const float VOLTAGE_DROP = 1.5;
const float BALL_SPACING_WAIT_TIME = 1.0;
const double ANGLE_THRESHOLD = 5.0;

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
	AutoController (RobotDrive *drive, Gyro *gyro);
	
	void GoToBallOne();
	void TurnNorth();
	void TurnEast();
	bool IsTracked();
	bool HasBall();
	void TurnToOurTarget();
	void TurnToEnemyTarget();
	void Orientation();
	
	RobotDrive *a_base;
	Gyro *a_gyro;
	PIDOutput *a_PIDOutput;
	PIDController *a_turnController;
}; 

#endif
