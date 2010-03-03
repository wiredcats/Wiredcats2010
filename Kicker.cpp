#include "Kicker.h" 

Kicker::Kicker():
winch(SPIKE_NUM) {
	servo = new Servo(2);
	compressor = new Compressor(1,1);
	firesolenoid = new Solenoid(8,1);
	ktooth = new Kickertooth(2);
	backdriveEnabled = false;
}

void Kicker::StartCompressor() {
	compressor->Start();
}

void Kicker::MoveKicker(KickerSetting ks) {
	switch(ks) {
	case kWinchUp:
		servo->Set(0.1);
		winch.Set(Relay::kReverse);
		break;
	case kWinchStop:
		servo->Set(0.9);
		if (!backdriveEnabled)
			winch.Set(Relay::kOff);
		break;
	default:
		// Oh nose
		break;
	}
}

void Kicker::UnlockServo() {
	servo->Set(0.9);
}

void Kicker::LockServo() {
	servo->Set(0.1);
}

void Kicker::EngageFireSolenoid() {
	firesolenoid->Set(true);
}

void Kicker::DisengageFireSolenoid() {
	firesolenoid->Set(false);
}

void Kicker::RunBackdrive() {
	winch.Set(Relay::kForward);
	backdriveEnabled = true;
}

void Kicker::StopBackdrive(){
	winch.Set(Relay::kOff);
	backdriveEnabled = false;
}

bool Kicker::BackdriveEnabled() {
	return backdriveEnabled;
}

void Kicker::RunPeriod(){
	if (ktooth->GetToothCount() < 500) {
		MoveKicker(Kicker::kWinchUp); 
	} else {
		MoveKicker(Kicker::kWinchStop);
	}
}
