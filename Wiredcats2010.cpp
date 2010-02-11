#include "Wiredcats2010.h"

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
	
	AxisCamera *camera;
	PIDController *turnController;
	
	Compressor *compressor;
	
	RobotDrive *drive;
	PIDOutput *drivePIDOutput;
	
	bool loopingPid;

public:
	Wiredcats2010(void):
		rlog("testlog.txt"), board(), kicker(),
		jagFrontRight(4), jagBackRight(5), jagFrontLeft(2), jagBackLeft(3)
	{
		// Constructor
		rlog.setMode("CNST");
		rlog.addLine("Opening constructor...");
		
		gyro = new Gyro(1);
		drive = new RobotDrive(jagFrontLeft, jagBackLeft, jagFrontRight, jagBackRight);
		drivePIDOutput = new DrivePID(drive);
		camera = &(AxisCamera::GetInstance());
		turnController= new PIDController(PROPORTION,
							INTEGRAL,
							DERIVATIVE,
							gyro,
							drivePIDOutput,
							0.02);
		compressor = new Compressor(1,1);
		compressor->Start();
		rlog.addLine("Sucessfully started constructor, running program...");
		 
		GetWatchdog().SetExpiration(0.1);
	}
	
	void Autonomous(void)
	{
		GetWatchdog().SetEnabled(false);
		// Start up camera
		camera = &(AxisCamera::GetInstance());
		camera->WriteResolution(AxisCamera::kResolution_320x240);
		camera->WriteBrightness(0);
		/*
		rlog.setMode("AUTO");
		rlog.startTimer();
		
		rlog.addLine("Entered autonomous!");
		
		// Set up PID
		gyro->Reset();
		turnController->SetInputRange(-360.0, 360.0);
		turnController->SetOutputRange(-0.6, 0.6);
		turnController->SetTolerance(1.0 / 90.0 * 100);
		turnController->Disable();
		
		//First block of code: Go to Ball #
		rlog.addLine("Entering first block of auto code...");
		int ballNumber = 7; //Filler for read text file number
		switch (ballNumber) {
		case 7:
			//Use PID + drive to turn
			turnController->Enable();
			while(jagFrontRight.GetOutputVoltage()){
				turnController->SetSetpoint(-BALL_ANGLE_1);
			}
			drive->Drive(1,0);
			Wait(BALL_WAIT_1);//Filler for timer...
			turnController->Disable();
			break;
		default:
			//OH NOEZ!
			//Panic();
			break;
		}
		//Autotarget, just Copy Pasta
		if (camera->IsFreshImage()) {
			ColorImage *image = camera->GetImage();
			vector<Target> targets = Target::FindCircularTargets(image); //Possible memory leak?
			delete image;
			
			rlog.addLine("Attempting to autotrack target...");
			
			if (targets.size() > 0 && targets[0].m_score > MINIMUM_SCORE) {
				double initHorizontalAngle = targets[0].GetHorizontalAngle(); //Possible memory leak?
				
				if (angleWithinThreshold(initHorizontalAngle)) {
					rlog.addLine("Found target, tracked (without PID)");
					// Light up LED
				} else {
					turnController->Enable();
					
					rlog.addLine("Found target, entering PID loop");
					
					double angleTurn = initHorizontalAngle + gyro->GetAngle();
					turnController->SetSetpoint(angleTurn);
				}
			} else {
				rlog.addLine("Found no targets");
				
				turnController->Disable();
			}
		}
		//Kick!
		
		//Second block of code: Go to another ball using text directions
		/*
		 * Idea for numbering: 
		 * N - 1, E - 2, S - 3, W - 4
		 * NW - 14, NE - 12, SW - 34, SE - 32
		 */
	/*	
		//Fancy for loop reading every line after the first (really necessary?)
		int directions = 1; //Filler: for loop goes through each line, stopping at . and reading off value?
		switch (directions) { //This switch statment uses numbers for compass directions for now.
		case 1:
			//Use PID + drive to turn
			turnController->Enable();
			while(jagFrontRight.GetOutputVoltage()){
				turnController->SetSetpoint(NORTH_1); //Dunno how to implement the difference factor
			}
			drive->Drive(1,0);
			Wait(BALL_WAIT_1);
			turnController->Disable();
			break;
		default:
			//OH NOEZ!
			break;
		}
		//Autotarget, just Copy Pasta
		if (camera->IsFreshImage()) {
			ColorImage *image = camera->GetImage();
			vector<Target> targets = Target::FindCircularTargets(image); //Possible memory leak?
			delete image;
			
			rlog.addLine("Attempting to autotrack target...");
			
			if (targets.size() > 0 && targets[0].m_score > MINIMUM_SCORE) {
				double initHorizontalAngle = targets[0].GetHorizontalAngle(); //Possible memory leak?
				
				if (angleWithinThreshold(initHorizontalAngle)) {
					rlog.addLine("Found target, tracked (without PID)");
					// Light up LED
				} else {
					turnController->Enable();
					
					rlog.addLine("Found target, entering PID loop");
					
					double angleTurn = initHorizontalAngle + gyro->GetAngle();
					turnController->SetSetpoint(angleTurn);
				}
			} else {
				rlog.addLine("Found no targets");
				
				turnController->Disable();
			}
		}
		*/
		//Kickers away!
		
		//Third block of code: Get away.
		//Strategy/driver dependent, so we'll worry later.
	}
	
	void OperatorControl(void)
	{
		GetWatchdog().SetEnabled(true);
		
		rlog.resetTimer();
		rlog.setMode("TELE");
		
		rlog.addLine("Entered teleop!");
		
		// Set up PID
		gyro->Reset();
		
		loopingPid = false;
		
		// Start up camera
		//camera = &(AxisCamera::GetInstance());
		
		rlog.startTimer();
		
		while (IsOperatorControl())
		{
			GetWatchdog().Feed();
			
			jagFrontRight.GetOutputVoltage();
			/*
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
							rlog.addLine("Found target, tracked (without PID)");
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
				
				// Cancel autotracking if joystick movement is detected
				if (board.GetLeftJoy()->GetY() > AUTO_CANCEL_THRESH || 
						board.GetLeftJoy()->GetY() < -AUTO_CANCEL_THRESH ||
						board.GetRightJoy()->GetY() > AUTO_CANCEL_THRESH || 
						board.GetRightJoy()->GetY() < -AUTO_CANCEL_THRESH) {
					rlog.addLine("User drive detected, leaving PID");
					turnController->Disable();
					loopingPid = false;
				}
			} else {*/
				drive->TankDrive(board.GetLeftJoy()->GetY(),
								 board.GetRightJoy()->GetY());
			//}
			
			Wait(0.005);
		}
	}
};

START_ROBOT_CLASS(Wiredcats2010);

