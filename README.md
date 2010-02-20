Westminster Wiredcats 2010 C++ Code
===================================

The following repository holds the C++ code of The Westminster Wiredcats (FRC #2415) for the
2010 season of *FIRST* robotics. The main code lies in Wiredcats2010.cpp.

File Hierarchy
--------------

* **Wiredcats2010.cpp**: The main code. Contains autonomous/teleoperation instructions as well as the custom PID classes and autotracking.

* **Autonomous.cpp**: Holds the AutonomousController class and manages all of our autonomous code. It goes to an initial ball and then goes North/South/East/West to the other balls and shoots. Uses CAN to measure voltage drop for the roller and sense when to kick the ball.

* **Log.cpp**: A log system that creates a file on the cRIO and writes lines of text to it. Useful for collecting data during a match.

* **ControlBoard.cpp**: Our configuration for our control board. We separated it into its own class to keep the code clean and starve the *Wiredcats.cpp* file.

* **Kicker.cpp**: The code for our kicker. Manages all the actions including winching back the kicker (using encoders) and releasing it.

* **Target.cpp**: The same Target.cpp file found in the 2010ImageExample example project.

* **CAN**: The CAN/2CAN libraries