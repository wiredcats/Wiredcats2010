#include "Wiredcats2010.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */

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

class Wiredcats2010 : public SimpleRobot
{
	Log rlog;
	
	ControlBoard board;
	Kicker kicker;
	
	HSLImage image;
	Gyro *gyro;
	
	CANJaguar jagFrontRight;
	CANJaguar jagBackRight;
	CANJaguar jagFrontLeft;
	CANJaguar jagBackLeft;
	
	RobotDrive *drive;
	PIDOutput *drivePIDOutput;
	
	PIDController *turnController;
	
	AxisCamera *camera;
	
	bool loopingPid;

public:
	Wiredcats2010(void):
		rlog("testlog.txt"), board(), kicker(),
		jagFrontRight(4), jagBackRight(5), jagFrontLeft(2), jagBackLeft(3)
	{
		// Constructor
		rlog.addLine("Opening constructor...");
		
		gyro = new Gyro(1);
		drive = new RobotDrive(jagFrontLeft, jagBackLeft, jagFrontRight, jagBackRight);
		drivePIDOutput = new DrivePID(drive);
		
		camera = &(AxisCamera::GetInstance());
		camera->WriteResolution(AxisCamera::kResolution_320x240);
		camera->WriteBrightness(0);
		
		turnController = new PIDController( PROPORTION,
								INTEGRAL,
								DERIVATIVE,
								gyro,
								drivePIDOutput,
								0.02);
		
		turnController->SetInputRange(-360.0, 360.0);
		turnController->SetOutputRange(-0.6, 0.6);
		turnController->SetTolerance(1.0 / 90.0 * 100);
		turnController->Disable();
		
		rlog.addLine("Sucessfully started constructor, running program...");
		
		GetWatchdog().SetExpiration(0.1);
	}
	
	void Autonomous(void)
	{
		GetWatchdog().SetEnabled(false);
		
		rlog.addLine("Entered autonomous!");
		
		gyro->Reset();
		
		// double initRollerVoltage = jagRoller.GetOutputVoltage();
		
		int ballNumber;
		
		switch (ballNumber) {
		case 1:
			rlog.addLine("Turning towards Ball 1");
			turnController->Enable();
			turnController->SetSetpoint(CLOSE_OFFSET_ANGLE);
			
			while (DriveIsMoving()) {
				Wait(0.02);
			}
			
			rlog.addLine("Turned towards Ball 1, approaching");
			drive->Drive(AUTO_DRIVE_SPEED, 0);
			Wait(CLOSE_OFFSET_BALL_WAIT);
			drive->Drive(0, 0);
			
			// if (jagRoller.GetOutputVoltage() < initRollerVoltage - ROLL_VOLT_THRESH) {
				rlog.addLine("Ball 1 found! Tracking towards target...");
				if (TurnTowardsOurTarget()) {
					rlog.addLine("Successfully tracked target! Kicking Ball 1...");
					KickBallInAuto();
				} else {
					rlog.addLine("Could not find our target!");
				}
			// } else {
				// rlog.addLine("Ball 1 not found, aborting! Attempting to track next ball");
				// break;
			// }
			
			rlog.addLine("Kicked Ball 1, moving to next ball...");
			break;
		case 2:
			rlog.addLine("Turning towards Ball 2");
			turnController->Enable();
			turnController->SetSetpoint(MID_OFFSET_ANGLE);
			
			while (DriveIsMoving()) {
				Wait(0.02);
			}
			
			rlog.addLine("Turned towards Ball 2, approaching");
			drive->Drive(AUTO_DRIVE_SPEED, 0);
			Wait(MID_OFFSET_BALL_WAIT);
			drive->Drive(0, 0);
			
			// if (jagRoller.GetOutputVoltage() < initRollerVoltage - ROLL_VOLT_THRESH) {
				rlog.addLine("Ball 2 found! Tracking towards target...");
				if (TurnTowardsOurTarget()) {
					rlog.addLine("Successfully tracked target! Kicking Ball 2...");
					KickBallInAuto();
				} else {
					rlog.addLine("Could not find our target!");
				}
			// } else {
				// rlog.addLine("Ball 2 not found, aborting! Attempting to track next ball");
				// break;
			// }
			
			rlog.addLine("Kicked Ball 2, moving to next ball...");
			break;
		case 3:
			rlog.addLine("Turning towards Ball 3");
			turnController->Enable();
			turnController->SetSetpoint(FAR_OFFSET_ANGLE);
			
			while (DriveIsMoving()) {
				Wait(0.02);
			}
			
			rlog.addLine("Turned towards Ball 3, approaching");
			drive->Drive(AUTO_DRIVE_SPEED, 0);
			Wait(FAR_OFFSET_BALL_WAIT);
			drive->Drive(0, 0);
			
			// if (jagRoller.GetOutputVoltage() < initRollerVoltage - ROLL_VOLT_THRESH) {
				rlog.addLine("Ball 3 found! Tracking towards target...");
				if (TurnTowardsOurTarget()) {
					rlog.addLine("Successfully tracked target! Kicking Ball 3...");
					KickBallInAuto();
				} else {
					rlog.addLine("Could not find our target!");
				}
			// } else {
				// rlog.addLine("Ball 3 not found, aborting! Attempting to track next ball");
				// break;
			// }
			
			rlog.addLine("Kicked Ball 3, moving to next ball...");
			break;
		
		case 4:
			rlog.addLine("Approaching Ball 4");
			drive->Drive(AUTO_DRIVE_SPEED, 0);
			Wait(BALL_4_WAIT);
			drive->Drive(0, 0);
			
			// if (jagRoller.GetOutputVoltage() < initRollerVoltage - ROLL_VOLT_THRESH) {
				rlog.addLine("Ball 4 found! Tracking towards target...");
				if (TurnTowardsOurTarget()) {
					rlog.addLine("Successfully tracked target! Kicking Ball 4...");
					KickBallInAuto();
				} else {
					rlog.addLine("Could not find our target!");
				}
			// } else {
				// rlog.addLine("Ball 4 not found, aborting! Attempting to track next ball");
				// break;
			// }
			
			rlog.addLine("Kicked Ball 4, moving to next ball...");
			break;
		case 5:
			rlog.addLine("Approaching Ball 5");
			drive->Drive(AUTO_DRIVE_SPEED, 0);
			Wait(BALL_5_WAIT);
			drive->Drive(0, 0);
			
			// if (jagRoller.GetOutputVoltage() < initRollerVoltage - ROLL_VOLT_THRESH) {
				rlog.addLine("Ball 5 found! Tracking towards target...");
				if (TurnTowardsOurTarget()) {
					rlog.addLine("Successfully tracked target! Kicking Ball 5...");
					KickBallInAuto();
				} else {
					rlog.addLine("Could not find our target!");
				}
			// } else {
				// rlog.addLine("Ball 5 not found, aborting! Attempting to track next ball");
				// break;
			// }
			
			rlog.addLine("Kicked Ball 5, moving to next ball...");
			break;
		case 6:
			rlog.addLine("Approaching Ball 6");
			drive->Drive(AUTO_DRIVE_SPEED, 0);
			Wait(BALL_6_WAIT);
			drive->Drive(0, 0);
			
			// if (jagRoller.GetOutputVoltage() < initRollerVoltage - ROLL_VOLT_THRESH) {
				rlog.addLine("Ball 6 found! Tracking towards target...");
				if (TurnTowardsOurTarget()) {
					rlog.addLine("Successfully tracked target! Kicking Ball 6...");
					KickBallInAuto();
				} else {
					rlog.addLine("Could not find our target!");
				}
			// } else {
				// rlog.addLine("Ball 6 not found, aborting! Attempting to track next ball");
				// break;
			// }
			
			rlog.addLine("Kicked Ball 6, moving to next ball...");
			break;
		
		case 7:
			rlog.addLine("Turning towards Ball 7");
			turnController->Enable();
			turnController->SetSetpoint(-CLOSE_OFFSET_ANGLE);
			
			while (DriveIsMoving()) {
				Wait(0.02);
			}
			
			rlog.addLine("Turned towards Ball 7, approaching");
			drive->Drive(AUTO_DRIVE_SPEED, 0);
			Wait(-CLOSE_OFFSET_BALL_WAIT);
			drive->Drive(0, 0);
			
			// if (jagRoller.GetOutputVoltage() < initRollerVoltage - ROLL_VOLT_THRESH) {
				rlog.addLine("Ball 7 found! Tracking towards target...");
				if (TurnTowardsOurTarget()) {
					rlog.addLine("Successfully tracked target! Kicking Ball 7...");
					KickBallInAuto();
				} else {
					rlog.addLine("Could not find our target!");
				}
			// } else {
				// rlog.addLine("Ball 7 not found, aborting! Attempting to track next ball");
				// break;
			// }
			
			rlog.addLine("Kicked Ball 7, moving to next ball...");
			break;
		case 8:
			rlog.addLine("Turning towards Ball 8");
			turnController->Enable();
			turnController->SetSetpoint(-MID_OFFSET_ANGLE);
			
			while (DriveIsMoving()) {
				Wait(0.02);
			}
			
			rlog.addLine("Turned towards Ball 8, approaching");
			drive->Drive(AUTO_DRIVE_SPEED, 0);
			Wait(MID_OFFSET_BALL_WAIT);
			drive->Drive(0, 0);
			
			// if (jagRoller.GetOutputVoltage() < initRollerVoltage - ROLL_VOLT_THRESH) {
				rlog.addLine("Ball 8 found! Tracking towards target...");
				if (TurnTowardsOurTarget()) {
					rlog.addLine("Successfully tracked target! Kicking Ball 8...");
					KickBallInAuto();
				} else {
					rlog.addLine("Could not find our target!");
				}
			// } else {
				// rlog.addLine("Ball 8 not found, aborting! Attempting to track next ball");
				// break;
			// }
			
			rlog.addLine("Kicked Ball 8, moving to next ball...");
			break;
		case 9:
			rlog.addLine("Turning towards Ball 9");
			turnController->Enable();
			turnController->SetSetpoint(FAR_OFFSET_ANGLE);
			
			while (DriveIsMoving()) {
				Wait(0.02);
			}
			
			rlog.addLine("Turned towards Ball 9, approaching");
			drive->Drive(AUTO_DRIVE_SPEED, 0);
			Wait(-FAR_OFFSET_BALL_WAIT);
			drive->Drive(0, 0);
			
			// if (jagRoller.GetOutputVoltage() < initRollerVoltage - ROLL_VOLT_THRESH) {
				rlog.addLine("Ball 9 found! Tracking towards target...");
				if (TurnTowardsOurTarget()) {
					rlog.addLine("Successfully tracked target! Kicking Ball 9...");
					KickBallInAuto();
				} else {
					rlog.addLine("Could not find our target!");
				}
			// } else {
				// rlog.addLine("Ball 9 not found, aborting! Attempting to track next ball");
				// break;
			// }
			
			rlog.addLine("Kicked Ball 9, moving to next ball...");
			break;	
		
		default:
			rlog.addLine("EXTREME ERROR: COULD NOT FIND VALUE TO MOVE TO NEXT BALL! MOVING TO POSITION 4 AND DISABLING");
			drive->Drive(AUTO_DRIVE_SPEED, 0);
			Wait(BALL_4_WAIT);
			drive->Drive(0, 0);
		}
	}
	
	void OperatorControl(void)
	{
		GetWatchdog().SetEnabled(true);
		
		rlog.addLine("Entered teleop!");
		
		// Set up PID
		gyro->Reset();
		
		loopingPid = false;
		
		while (IsOperatorControl())
		{
			GetWatchdog().Feed();
			
			jagFrontRight.GetOutputVoltage();
			
			// Autotracking
			if (board.GetLeftJoy()->GetRawButton(1)) {
				if (camera->IsFreshImage()) {
					ColorImage *image = camera->GetImage();
					vector<Target> targets = Target::FindCircularTargets(image);
					delete image;
					
					rlog.addLine("Attempting to autotrack target...");
					
					if (targets.size() > 0 && targets[0].m_score > MINIMUM_SCORE) {
						double initHorizontalAngle = targets[0].GetHorizontalAngle();
						
						if (angleWithinThreshold(initHorizontalAngle)) {
							rlog.addLine("Found target, tracked (without  PID)");
							// Light up LED
						} else {
							turnController->Enable();
							loopingPid = true;
							
							rlog.addLine("Found target, entering PID loop");
							
							double angleTurn = initHorizontalAngle + gyro->GetAngle();
							turnController->SetSetpoint(angleTurn);
						}
					} else {
						rlog.addLine("Found no targets");
						
						turnController->Disable();
						loopingPid = false;
					}
				}
			}
			
			// Kicker
			if (board.GetRightJoy()->GetRawButton(1)) {
				kicker.disengageServo();
			}
			
			if (board.GetRightJoy()->GetRawButton(2)) {
				kicker.engageServo();
			}
			
			// Drive or Control PID
			if (loopingPid) {
				// No motors moving, must be tracked
				if (!DriveIsMoving()) {
					rlog.addLine("Motors not moving, assuming tracked. Leaving PID");
					turnController->Disable();
					loopingPid = false;
				}
				
				// Cancel autotracking if joystick movement is detected
				if (board.GetLeftJoy()->GetY() > AUTO_CANCEL_THRESH || 
						board.GetLeftJoy()->GetY() < -AUTO_CANCEL_THRESH ||
						board.GetRightJoy()->GetY() > AUTO_CANCEL_THRESH || 
						board.GetRightJoy()->GetY() < -AUTO_CANCEL_THRESH) {
					rlog.addLine("User drive detected, leaving PID");
					turnController->Disable();
					loopingPid = false;
				}
			} else {
				drive->TankDrive(board.GetLeftJoy()->GetY(),
								 board.GetRightJoy()->GetY());
			}
			
			Wait(0.005);
		}
	}
	
	void KickBallInAuto() {
		// Kick ball :-)
	}
	
	bool TurnTowardsOurTarget() {
		if (camera->IsFreshImage()) {
			ColorImage *image = camera->GetImage();
			vector<Target> targets = Target::FindCircularTargets(image);
			delete image;
			
			if (targets.size() > 0 && targets[0].m_score > MINIMUM_SCORE) {
				turnController->Enable();
				turnController->SetSetpoint(gyro->GetAngle() + targets[0].GetHorizontalAngle());
				
				while (DriveIsMoving()) {
					Wait(0.02);
				}
				
				turnController->Disable();
				return true;
			}
		}
		
		return false;
	}
	
	bool DriveIsMoving() {
		return jagFrontRight.Get() < MOTOR_MOVE_THRESH && jagFrontRight.Get() > -MOTOR_MOVE_THRESH ||
				jagFrontLeft.Get() < MOTOR_MOVE_THRESH && jagFrontLeft.Get() > -MOTOR_MOVE_THRESH ||
				jagBackRight.Get() < MOTOR_MOVE_THRESH && jagBackRight.Get() > -MOTOR_MOVE_THRESH ||
				jagBackLeft.Get() < MOTOR_MOVE_THRESH && jagBackLeft.Get() > -MOTOR_MOVE_THRESH;
	}
};

START_ROBOT_CLASS(Wiredcats2010);

