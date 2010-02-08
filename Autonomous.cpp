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
 * 
 */

AutoController::AutoController(RobotDrive *drive, Gyro *gyro, CANJaguar *jaguar)
{
	a_base = drive;
	a_gyro = gyro;
	a_jag = jaguar;
	a_PIDOutput = new DrivePID(a_base);
	a_turnController = new PIDController(PROPORTION,
							INTEGRAL,
							DERIVATIVE,
							a_gyro,
							a_PIDOutput,
							0.02);
}

//Go To Ball #
void AutoController::GoToBallOne()
{	
	float initJagVoltage = a_jag->GetOutputVoltage();
	
	a_gyro->Reset();
	a_turnController->SetInputRange(-360.0, 360.0);
	a_turnController->SetOutputRange(-0.6, 0.6);
	a_turnController->SetTolerance(1.0 / 90.0 * 100);
	a_turnController->Disable();
	
	TurnNorth();
	a_base->Drive(1,0);
	Wait(BALL_SPACING_WAIT_TIME);
	TurnEast();
	while(!HasBall(initJagVoltage)) {
		a_base->Drive(1,0);
	}
	a_base->Drive(0,0);
	TurnToOurTarget();
	//Kick Ball
}

//Turn Compass Direction
void AutoController::TurnNorth()
{		
	double angle = a_gyro->GetAngle();
	if(angle < 90+ANGLE_THRESHOLD && angle > 90-ANGLE_THRESHOLD){
		//Filler, most likely print something
	} else {
		a_turnController->Enable();
		while(a_jag->Get()!=0.0){
			a_turnController->SetSetpoint(90);
		}
	}
}

void AutoController::TurnEast()
{		
	double angle = a_gyro->GetAngle();
	if(angle < 0+ANGLE_THRESHOLD && angle > 0-ANGLE_THRESHOLD){
		//Filler, most likely print something
	} else {
		a_turnController->Enable();
		while(a_jag->Get()!=0.0){
			a_turnController->SetSetpoint(0);
		}
	}
}

//Turn to Targets
void AutoController::TurnToOurTarget()
{
	double angle = a_gyro->GetAngle();
		if(angle < 0+ANGLE_THRESHOLD && angle > 0-ANGLE_THRESHOLD){
			//Filler, most likely print something
		} else {
			a_turnController->Enable();
			while(a_jag->Get()!=0.0){
				a_turnController->SetSetpoint(0);
			}
		}
	AxisCamera &camera = AxisCamera::GetInstance();
		camera.WriteResolution(AxisCamera::kResolution_320x240);
		camera.WriteBrightness(0);
			
	if (camera.IsFreshImage()) {
		ColorImage *image = camera.GetImage();
		vector<Target> targets = Target::FindCircularTargets(image);
		delete image;
		
		if (targets.size() > 0 && targets[0].m_score > MINIMUM_SCORE) {
			double initHorizontalAngle = targets[0].GetHorizontalAngle();
			
			if (angleWithinThreshold(initHorizontalAngle)) {
				//Filler text
			} else {
				a_turnController->Enable();
				double angleTurn = initHorizontalAngle + a_gyro->GetAngle();
				a_turnController->SetSetpoint(angleTurn);
			}
		}
	}
}

//Check Robot Info
bool AutoController::IsTracked()
{
	bool tracked = false;
	
	AxisCamera &camera = AxisCamera::GetInstance();
			camera.WriteResolution(AxisCamera::kResolution_320x240);
			camera.WriteBrightness(0);
			
	if (camera.IsFreshImage()) {
			ColorImage *image = camera.GetImage();
			vector<Target> targets = Target::FindCircularTargets(image);
			delete image;
			
			if (targets.size() > 0 && targets[0].m_score > MINIMUM_SCORE) {
				double initHorizontalAngle = targets[0].GetHorizontalAngle();
				
				if (angleWithinThreshold(initHorizontalAngle)) {
					tracked = true;
				} else {
					a_turnController->Enable();
					double angleTurn = initHorizontalAngle + a_gyro->GetAngle();
					a_turnController->SetSetpoint(angleTurn);
					tracked = true;
				}
			}
	}
	return(tracked);
}

bool AutoController::HasBall(float initJagVoltage)
{
	return(initJagVoltage-(a_jag->GetOutputVoltage())>=VOLTAGE_DROP);
}
