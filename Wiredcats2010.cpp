#include "Wiredcats2010.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */
class RobotDemo : public SimpleRobot
{
	RobotDrive myRobot; // robot drive system
	Joystick stick;
	
	Log rlog;

public:
	RobotDemo(void):
		myRobot(1,2), stick(1), rlog("newthing.log")
	{
		rlog.addLine("Constructor");
		GetWatchdog().SetExpiration(0.1);
	}
	
	/**
	 * Drive left & right motors for 2 seconds then stop
	 * Woooooooooooooooooooooooooo!
	 */
	void Autonomous(void)
	{
		GetWatchdog().SetEnabled(false);
		
		rlog.addLine("Started Autonomous Mode");
		
		myRobot.Drive(0.5, 0.0); 	// drive forwards half speed
		Wait(2.0); 				//    for 2 seconds
		myRobot.Drive(0.0, 0.0); 	// stop robot
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void)
	{
		GetWatchdog().SetEnabled(true);
		
		rlog.addLine("Started Teleop Mode");
		
		// Start up camera
		AxisCamera &camera = AxisCamera::getInstance();
		camera.writeResolution(k320x240);
		camera.writeBrightness(0);
		
		while (IsOperatorControl())
		{
			GetWatchdog().Feed();
			
			myRobot.ArcadeDrive(stick);
			Wait(0.005);
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

