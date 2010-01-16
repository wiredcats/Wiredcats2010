#include "Gamepad.h"

Gamepad::Gamepad(UINT32 port) {
	stick = new Joystick(port);
}

bool Gamepad::buttonOnePressed() {
	return stick->GetRawButton(1);
}
