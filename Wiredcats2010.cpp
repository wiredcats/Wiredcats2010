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
	ControlBoard board;
	Kicker kicker;
	
	
	HSLImage image;
	Gyro *gyro;
	
	Log rlog;
	
	CANJaguar jagFrontRight;
	CANJaguar jagBackRight;
	CANJaguar jagFrontLeft;
	CANJaguar jagBackLeft;
	
	RobotDrive *drive;
	PIDOutput *drivePIDOutput;

public:
	Wiredcats2010(void):
		board(),kicker(), rlog("stuff.log"),
		jagFrontRight(4), jagBackRight(5), jagFrontLeft(2), jagBackLeft(3)
	{
		// Constructor
		gyro = new Gyro(1);
		drive = new RobotDrive(jagFrontLeft, jagBackLeft, jagFrontRight, jagBackRight);
		drivePIDOutput = new DrivePID(drive);
		
		GetWatchdog().SetExpiration(0.1);
	}
	
	void Autonomous(void)
	{
		GetWatchdog().SetEnabled(false);
		
		// Autonomous
		drive->Drive(0.5, 0.0);
		Wait(2.0);
		drive->Drive(0.0, 0.0);
	}
	
	void OperatorControl(void)
	{
		GetWatchdog().SetEnabled(true);
		
		// Set up PID
		gyro->Reset();
		PIDController turnController( PROPORTION,
								INTEGRAL,
								DERIVATIVE,
								gyro,
								drivePIDOutput,
								0.02);
		
		turnController.SetInputRange(-360.0, 360.0);
		turnController.SetOutputRange(-0.6, 0.6);
		turnController.SetTolerance(1.0 / 90.0 * 100);
		turnController.Disable();
		
		// Start up camera
		AxisCamera &camera = AxisCamera::getInstance();
		camera.writeResolution(k320x240);
		camera.writeBrightness(0);
		
		while (IsOperatorControl())
		{
			GetWatchdog().Feed();
			
			jagFrontRight.GetOutputVoltage();
			
			// Autotracking
			if (board.GetLeftJoy()->GetRawButton(1)) {
				if (camera.freshImage()) {
					ColorImage *image = camera.GetImage();
					vector<Target> targets = Target::FindCircularTargets(image);
					delete image;
				
					if (targets.size() > 0 && targets[0].m_score > MINIMUM_SCORE){
						turnController.Enable();
						double angleTurn = targets[0].GetHorizontalAngle() + gyro->GetAngle();
						turnController.SetSetpoint(angleTurn);
					} else {
						turnController.Disable();
					}
				}
			}
			if (board.GetRightJoy()->GetRawButton(1)){
				kicker.DisengageServo();
			}
			// Drive
			if (false) {
				drive->TankDrive(board.GetLeftJoy()->GetY(),
								  board.GetRightJoy()->GetY());
			}
			
			Wait(0.005);
		}
	}
};

START_ROBOT_CLASS(Wiredcats2010);

