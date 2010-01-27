#include "WPILib.h"
#include "CANJaguar.h"

/**
 * This is a demo program showing the use of the SimpleRobot base class.
 * It uses CAN to control the Jaguars instead of PWM.
 */ 
class CANRobotDemo : public SimpleRobot
{
	CANJaguar leftJag;	// CAN attached Jag for the Left motor
	CANJaguar rightJag;	// CAN attached Jag for the Right motor
	RobotDrive myRobot; // robot drive system
	Joystick stick; // only joystick

public:
	CANRobotDemo(void):
		leftJag(2),		// These must be initialized in the same order
		rightJag(4),	// as they are declared above.
		myRobot(leftJag, rightJag),
		stick(1)
	{
		GetWatchdog().SetExpiration(100);
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
		GetWatchdog().SetEnabled(false);
		myRobot.Drive(0.5, 0.0); 	// drive forwards half speed
		Wait(2.0); 				//    for 2 seconds
		myRobot.Drive(0.0, 0.0); 	// stop robot
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void)
	{
		printf("In OperatorControl\n");
		GetWatchdog().SetEnabled(true);
		while (IsOperatorControl() && !IsDisabled())
		{
			GetWatchdog().Feed();
			myRobot.ArcadeDrive(stick); // drive with arcade style (use right stick)
			// Print out some information about the Left motor.
			printf ("Left=> ");
			printf ("Bus: %5.2f V ", leftJag.GetBusVoltage());
			printf ("Out: %6.2f V ", leftJag.GetOutputVoltage());
			printf ("Cur: %4.1f A ", leftJag.GetOutputCurrent());
			printf ("Temp: %5.1f Deg C ", leftJag.GetTemperature());
			printf ("LimSw: %s%s ", leftJag.GetForwardLimitOK() ? "F":"-",
					leftJag.GetReverseLimitOK() ? "R":"-");
			printf ("PwrCyc: %d ", leftJag.GetPowerCycled() ? 1:0);
			printf ("\n");

			Wait(0.02);
		}
	}
};

START_ROBOT_CLASS(CANRobotDemo);

