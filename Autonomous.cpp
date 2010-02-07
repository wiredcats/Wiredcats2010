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

void GoToBallOne(RobotDrive *drive,Gyro *gyro, PIDController &turnController)
{	
	TurnNorth(drive,gyro,turnController);
	drive->Drive(1,0);
	Wait(BALL_SPACING_WAIT_TIME);
	TurnEast(drive,gyro,turnController);
	while(!HasBall()) {
		drive->Drive(1,0);
	}
	TurnToOurTarget(drive,gyro,turnController);
	//Kick Ball
}

void TurnNorth(RobotDrive *drive, Gyro *gyro, PIDController &turnController)
{
	double angle = gyro->GetAngle();
	if(angle < 90+ANGLE_THRESHOLD && angle > 90-ANGLE_THRESHOLD){
		//Filler, most likely print something
	} else {
		turnController.Enable();
		turnController.SetSetpoint(90);
		turnController.Disable();
	}
}
