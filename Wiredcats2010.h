#ifndef WIREDCATS2010_H_
#define WIREDCATS2010_H_

// Constants
#define MINIMUM_SCORE 0.01
#define AUTO_THRESHOLD 4

#define AUTO_CANCEL_THRESH 0.2

#define PROPORTION 0.1
#define INTEGRAL 0.0
#define DERIVATIVE 0.5

#define VOLTAGE_DROP 1.5

#define NORTH_1 270
#define NORTH_2 -90
#define EAST_1 0
#define EAST_2 360
#define SOUTH_1 90
#define SOUTH_2 -270
#define WEST_1 180
#define WEST_2 -180

#define BALL_ANGLE_1 45
#define BALL_ANGLE_2 35
#define BALL_ANGLE_3 25

#define BALL_WAIT_1 2.0
#define BALL_WAIT_2 2.5
#define BALL_WAIT_3 3.0

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
