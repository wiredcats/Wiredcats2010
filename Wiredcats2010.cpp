#include "Wiredcats2010.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */

class RobotDemo : public SimpleRobot
{
	ControlBoard board;
	
	HSLImage image;
	Gyro gyro;
	
	Log rlog;
	
	RobotDrive myRobot; // robot drive system

public:
	RobotDemo(void):
		board(), gyro(1), rlog("stuff.log"),
        myRobot(1,2)
        
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
		
		gyro.Reset();
		
		rlog.addLine("Started Teleop Mode");
		
		// Start up camera
		AxisCamera &camera = AxisCamera::getInstance();
		camera.writeResolution(k320x240);
		camera.writeBrightness(0);
		
		while (IsOperatorControl())
		{
			GetWatchdog().Feed();
			
			printf("\n%g = angle",gyro.GetAngle());
			
			// Autotracking
			if (camera.freshImage()) {
				ColorImage *image = camera.GetImage();
				vector<Target> targets = Target::FindCircularTargets(image);
				delete image;
				
				if (targets.size() > 0 && targets[0].m_score > MINIMUM_SCORE){
					printf(" %f = horizontal angle", targets[0].GetHorizontalAngle());
					if (board.GetLeftJoy()->GetRawButton(1)) {
						double angleTurn = targets[0].GetHorizontalAngle()+gyro.GetAngle();
						double upperBound = gyro.GetAngle() + AUTO_THRESHOLD;
						double lowerBound = gyro.GetAngle() - AUTO_THRESHOLD;
						while (lowerBound <= gyro.GetAngle() && upperBound >= gyro.GetAngle()){
							GetWatchdog().Feed();
							
							printf("\ntracking gyro = %f", gyro.GetAngle());
							if(gyro.GetAngle() > angleTurn){
								myRobot.TankDrive(0.6, -0.6);
							} else {
								myRobot.TankDrive(-0.6,0.6);
							}
						} 
						myRobot.TankDrive(0.0,0.0);
					}
				}
			}
			
			myRobot.TankDrive(board.GetLeftJoy()->GetY(),
							  board.GetRightJoy()->GetY());
			
			Wait(0.005);
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

