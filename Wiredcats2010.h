#ifndef WIREDCATS2010_H_
#define WIREDCATS2010_H_

// Constants
#define MINIMUM_SCORE 0.01
#define AUTO_THRESHOLD 4

#define AUTO_CANCEL_THRESH 0.2

#define PROPORTION 0.1
#define INTEGRAL 0.0
#define DERIVATIVE 0.5

#define NORTH 1
#define EAST 2
#define SOUTH 3
#define WEST 4
#define NORTHEAST 12
#define NORTHWEST 14
#define SOUTHEAST 32
#define SOUTHWEST 34

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
