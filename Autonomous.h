#ifndef AUTONOMOUS_H_
#define AUTONOMOUS_H_

#include "WPILib.h"
#include "PIDController.h"

// Constants
const float VOLTAGE_DROP = 1.5;
const float BALL_SPACING_WAIT_TIME = 1.0;
const double ANGLE_THRESHOLD = 5.0;

// Functions
void GoToBallOne(RobotDrive *drive, Gyro *gyro, PIDController &turnController);
void TurnNorth(RobotDrive *drive, Gyro *gyro, PIDController &turnController);
void TurnEast(RobotDrive *drive, Gyro *gyro, PIDController &turnController);
bool IsTracked();
bool HasBall();
void TurnToOurTarget(RobotDrive *drive, Gyro *gyro, PIDController &turnController);
void TurnToEnemyTarget();
void Orientation();

#endif
