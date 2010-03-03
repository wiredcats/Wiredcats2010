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
	// Devlog
	Log rlog;
	
	// Control board (joysticks, buttons, etc.)
	ControlBoard board;
	
	// Component objects
	Kicker kicker;
	Arm arm;
	
	// Camera components
	HSLImage image;
	AxisCamera *camera;
	
	// Sensors
	Gyro *gyro;
	Kickertooth *ktooth;
	
	// Drive and roller motors
	CANJaguar jagDriveLeftCenter;
	CANJaguar jagDriveLeftOuter;
	CANJaguar jagDriveRightOuter;
	CANJaguar jagDriveRightCenter;
	CANJaguar jagRoller;
	
	RobotDrive *drive;
	
	// Drive PID components
	PIDOutput *drivePIDOutput;
	PIDController *turnController;
	
	// Timers
	Timer *backdriveTimer;
	Timer *fireTimer;
	
	// Function-specific variables
	bool loopingPid;
	bool backdriveEnabled;

public:
	Wiredcats2010(void):
		rlog("testlog.txt"), board(), kicker(), arm(),
		jagDriveLeftCenter(4), jagDriveLeftOuter(5), jagDriveRightOuter(2), jagDriveRightCenter(3),
		jagRoller(7)
	{
		// Constructor
		rlog.setMode("CNST");
		rlog.addLine("Opening constructor...");
		
		// Open sensors
		gyro = new Gyro(1);
		ktooth = new Kickertooth(2);
		
		// Open drive and drive PIDs
		drive = new RobotDrive(jagDriveRightOuter,  jagDriveRightCenter, jagDriveLeftCenter, jagDriveLeftOuter);
		drivePIDOutput = new DrivePID(drive);
		
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
		
		// Open camera
		camera = &(AxisCamera::GetInstance());
		camera->WriteResolution(AxisCamera::kResolution_320x240);
		camera->WriteBrightness(0);
		
		// Open timers
		backdriveTimer = new Timer();
		backdriveTimer->Reset();
		fireTimer = new Timer();
		fireTimer->Reset();
		
		rlog.addLine("Sucessfully started constructor, running program...");
		 
		GetWatchdog().SetExpiration(0.1);
	}
	
	void Autonomous(void)
	{
		GetWatchdog().SetEnabled(false);
		
		rlog.setMode("AUTO");
		rlog.startTimer();
		
		rlog.addLine("Entered autonomous!");
		
		gyro->Reset();
		
		for(int counter=NUM_BALLS;counter>0;counter--){
			//Drive to a ball
			drive->Drive(AUTO_DRIVE_SPEED,0);
			Wait(STRAIGHT_WAIT);
			drive->Drive(0,0);
			
			//Winch Up
			kicker.MoveKicker(Kicker::kWinchUp);
			//Use Geartooth to tell if winched far enough back
			kicker.MoveKicker(Kicker::kWinchStop);
			
			//Start Backdrive
			rlog.addLine("Engaging backdrive...");
			kicker.RunBackdrive();
			
			Wait(BACKDRIVE_TIMER_LIMIT);
			
			rlog.addLine("Stopping backdrive, unlocking servo...");
			kicker.StopBackdrive();
			kicker.UnlockServo();
			
			//Fire Piston!
			rlog.addLine("FIRE IN THE HOLE!");
			kicker.EngageFireSolenoid();
			
			Wait(FIRE_TIMER_LIMIT);
			
			rlog.addLine("Disengaging fire piston...");
			kicker.DisengageFireSolenoid();
		}
	}
	
	void OperatorControl(void)
	{
		GetWatchdog().SetEnabled(true);
		
		rlog.resetTimer();
		rlog.setMode("TELE");
		
		rlog.addLine("Entered teleop!");
		
		// Set initial variable values
		//gyro->Reset();
		loopingPid = false;
		bool servoEnabled = false;
		backdriveEnabled = false;
		
		// Start timestamp timer for rlog
		rlog.startTimer();
		
		// Start the kicker compressor
		kicker.StartCompressor();
		
		while (IsOperatorControl())
		{
			GetWatchdog().Feed();
			
			// Run Kickertooth Period
			ktooth->RunPeriod();
			
			//CAN Voodoo...
			jagDriveLeftCenter.GetOutputVoltage();
			
			printf("geartooth: %d\n", ktooth->GetToothCount());
			
			// Autotracking
			if (board.GetLeftJoy()->GetRawButton(2)) {
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
			
			// Arm
			if (board.GetFakeJoy()->GetRawButton(10)) {
				if (!servoEnabled) {
					arm.SetServo(Arm::sRelease);
					Wait(0.5);
					servoEnabled = true;
				}
				arm.RunWinch(Arm::wUp);
			} else if (board.GetFakeJoy()->GetRawButton(11)){
				if (!servoEnabled) {
					arm.SetServo(Arm::sRelease);
					Wait(0.5);
					servoEnabled = true;
				}
				arm.RunWinch(Arm::wDown);
			} else {
				arm.RunWinch(Arm::wStop);
				if (servoEnabled) {
					Wait(0.2);
					arm.SetServo(Arm::sLock);
					servoEnabled = false;
				}
			}
			
			if (board.GetFakeJoy()->GetRawButton(6)) {
				arm.MoveArm(Arm::aRaise);
			} else if (board.GetFakeJoy()->GetRawButton(7)){
				arm.MoveArm(Arm::aLower);
			} else {
				arm.MoveArm(Arm::aStill);
			}
			
			if (board.GetFakeJoy()->GetRawButton(8)) {
				arm.ExtendArm(Arm::aExtend);
			} else if (board.GetFakeJoy()->GetRawButton(9)) {
				arm.ExtendArm(Arm::aRetract);
			} else {
				arm.ExtendArm(Arm::aStop);
			}
			
			// Kicker //
			// Winch Back
			if (board.GetFakeJoy()->GetRawButton(1)) {
				// rlog.addLine("Winching back...");
				kicker.MoveKicker(Kicker::kWinchUp);
			} else {
				kicker.MoveKicker(Kicker::kWinchStop);
			}
			
			// Run Backdrive -> release tension on dog gear
			if (backdriveTimer->Get() >= BACKDRIVE_TIMER_LIMIT) {
				rlog.addLine("Stopping backdrive, unlocking servo...");
				kicker.StopBackdrive();
				backdriveTimer->Stop();
				backdriveTimer->Reset();
				kicker.UnlockServo();
			} else {
				if (kicker.BackdriveEnabled()) {
					kicker.RunBackdrive();
				} else if (board.GetFakeJoy()->GetRawButton(3)) {
					rlog.addLine("Engaging backdrive...");
					kicker.RunBackdrive();
					backdriveTimer->Start();
				}
			}
			
			// Fire kicker (engage piston!)
			if (fireTimer->Get() >= FIRE_TIMER_LIMIT) {
				rlog.addLine("Disengaging fire piston...");
				kicker.DisengageFireSolenoid();
				fireTimer->Stop();
				fireTimer->Reset();
			} else {
				if (board.GetFakeJoy()->GetRawButton(2)) {
					rlog.addLine("FIRE IN THE HOLE!");
					kicker.EngageFireSolenoid();
					fireTimer->Start();
				}
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
		/*
		 * Winch Back (servo is locked
		 * Unlock servo
		 * run gears for a second
		 * set solenoid to true
		 */
	}
	
	bool TurnTowardsOurTarget() { 
		//Question: How do we know we're facing our target over the opponent's target?
		//Can we just put in a gyro command to turn in the general easterly direction?
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
		return jagDriveLeftCenter.Get() < MOTOR_MOVE_THRESH && jagDriveLeftCenter.Get() > -MOTOR_MOVE_THRESH ||
				jagDriveRightOuter.Get() < MOTOR_MOVE_THRESH && jagDriveRightOuter.Get() > -MOTOR_MOVE_THRESH ||
				jagDriveLeftOuter.Get() < MOTOR_MOVE_THRESH && jagDriveLeftOuter.Get() > -MOTOR_MOVE_THRESH ||
				jagDriveRightCenter.Get() < MOTOR_MOVE_THRESH &&  jagDriveRightCenter.Get() > -MOTOR_MOVE_THRESH;
	}
};

START_ROBOT_CLASS(Wiredcats2010);
