#ifndef WIREDCATS2010_H_
#define WIREDCATS2010_H_

// Constants
#define MINIMUM_SCORE 0.01
#define AUTO_THRESHOLD 4

#define AUTO_CANCEL_THRESH 0.2

#define PROPORTION 0.1
#define INTEGRAL 0.0
#define DERIVATIVE 0.5

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
#include "Autonomous.h"

#endif
