#include "Autonomous.h"

/**
 * Assumes Robot is lined up with the bump / driver station wall
 * and is about horizontally aligned with balls 4-6.
 * Where the balls are positioned:
 * 1 2 3
 * 4 5 6
 * 7 8 9
 * NOTE: The initial facing direction of the robot is called
 * 		 East, regardless of where magnetic East actually is.
 */

AutoController::AutoController(RobotDrive *drive, Gyro *gyro)
{
	a_base = drive;
	a_gyro = gyro;
	a_PIDOutput = new DrivePID(a_base);
	a_turnController = new PIDController(PROPORTION,
							INTEGRAL,
							DERIVATIVE,
							a_gyro,
							a_PIDOutput,
							0.02);
}

void AutoController::GoToBallOne()
{	
	a_gyro->Reset();
	a_turnController->SetInputRange(-360.0, 360.0);
	a_turnController->SetOutputRange(-0.6, 0.6);
	a_turnController->SetTolerance(1.0 / 90.0 * 100);
	a_turnController->Disable();
	
	TurnNorth();
	a_base->Drive(1,0);
	Wait(BALL_SPACING_WAIT_TIME);
	TurnEast();
	while(!HasBall()) {
		a_base->Drive(1,0);
	}
	TurnToOurTarget();
	//Kick Ball
}

void AutoController::TurnNorth()
{		
	double angle = a_gyro->GetAngle();
	if(angle < 90+ANGLE_THRESHOLD && angle > 90-ANGLE_THRESHOLD){
		//Filler, most likely print something
	} else {
		a_turnController->Enable();
		a_turnController->SetSetpoint(90);
	}
}
