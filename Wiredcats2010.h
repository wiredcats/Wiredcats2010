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

#define NUM_BALLS 3

const float ROLLER_SPEED = -1.0;

const float ROLL_VOLT_THRESH = 1.5;
const float MOTOR_MOVE_THRESH = 0.05;
const float BACKDRIVE_TIMER_LIMIT = 1.0;
const float FIRE_TIMER_LIMIT = 1.0;

const float STRAIGHT_WAIT = 2.0;

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
#include "Arm.h"
#include "Kickertooth.h"

#endif
