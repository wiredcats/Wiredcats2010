#include "ControlStation.h"

Joystick ControlStation::GetLeftJoy()
{
    
}

Joystick ControlStation::GetRightJoy()
{
    
}

bool ControlStation::buttonOnePressed() {
	return stick->GetRawButton(1);
}
