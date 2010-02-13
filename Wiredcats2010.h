#ifndef WIREDCATS2010_H_
#define WIREDCATS2010_H_

// Constants
#define MINIMUM_SCORE 0.01
#define AUTO_THRESHOLD 4

#define AUTO_CANCEL_THRESH 0.2

#define PROPORTION 0.1
#define INTEGRAL 0.0
#define DERIVATIVE 0.5

#define AUTO_DRIVE_SPEED 0.6

const float MOTOR_MOVE_THRESH = 0.05;

const float CLOSE_OFFSET_BALL_WAIT = 2.0;
const float MID_OFFSET_BALL_WAIT = 3.0;
const float FAR_OFFSET_BALL_WAIT = 4.0;
const float BALL_4_WAIT = 2.0;
const float BALL_5_WAIT = 3.0;
const float BALL_6_WAIT = 4.0;

const int CLOSE_OFFSET_ANGLE = 30;
const int MID_OFFSET_ANGLE = 20;
const int FAR_OFFSET_ANGLE = 10;

const int POSITIVE_NORTH_ANGLE = 90;
const int NEGATIVE_NORTH_ANGLE = -270;
const int POSITIVE_EAST_ANGLE = 0;
const int NEGATIVE_EAST_ANGLE = -360;
const int POSITIVE_SOUTH_ANGLE = 270;
const int NEGATIVE_SOUTH_ANGLE = -90;
const int POSITIVE_WEST_ANGLE = 180;
const int NEGATIVE_WEST_ANGLE = -180;

const int POSITIVE_NORTHEAST_ANGLE = 45;
const int NEGATIVE_NORTHEAST_ANGLE = -315;
const int POSITIVE_NORTHWEST_ANGLE = 135;
const int NEGATIVE_NORTHWEST_ANGLE = -225;
const int POSITIVE_SOUTHEAST_ANGLE = 315;
const int NEGATIVE_SOUTHEAST_ANGLE = -45;
const int POSITIVE_SOUTHWEST_ANGLE = 225;
const int NEGATIVE_SOUTHWEST_ANGLE = -135;

const float STRAIGHT_WAIT = 2.0;
const float DIAG_WAIT = 2.2;

// WPI library
#include "WPILib.h"

// Extra libraries
#include "Vision/AxisCamera.h"
#include "Vision/HSLImage.h"
#include "PIDController.h"

// Copy Pasta
#include "Target.h"

// Can Junk
#include "CAN/CANJaguar.h"

// 2415 classes
#include "Log.h"
#include "ControlBoard.h"
#include "Kicker.h"

#endif
