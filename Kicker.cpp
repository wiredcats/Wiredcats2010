#include "Kicker.h" 

Kicker::Kicker():
winch(SPIKE_NUM) {
	encoder = new Encoder(ENCODER_CHANNEL_1,ENCODER_CHANNEL_2);
	servo = new Servo(2);
	compressor = new Compressor(1,1);
	firesolenoid = new Solenoid(8,1);
	//dogsolenoid = new Solenoid(8, 1);
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

void Kicker::WinchToGear(GearStop gs) {
	switch(gs) {
	case gLow:
		break;
	case gMid:
		break;
	case gHigh:
		break;
	default:
		break;
	}
}

void Kicker::EngageFireSolenoid() {
	firesolenoid->Set(true);
}

void Kicker::DisengageFireSolenoid() {
	firesolenoid->Set(false);
}

float Kicker::GetEncoder() {
	return encoder->Get();
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

/*void Kicker::ResetEncoder() {
	encoder->Reset();
}

void Kicker::GoToLowGear() {
	if ((encoder->Get()) <= LOW_GEAR_DIST){
		spike->Set((Relay::Value)kForward);
	} else {
		spike->Set((Relay::Value)kOff);
	}
}

void Kicker::GoToMidGear() {
	if ((encoder->Get()) <= MID_GEAR_DIST){
		spike->Set((Relay::Value)kForward);
	} else {
		spike->Set((Relay::Value)kOff);
	}
}

void Kicker::GoToHighGear() {
	if ((encoder->Get()) <= HIGH_GEAR_DIST){
		spike->Set((Relay::Value)kForward);
	} else {
		spike->Set((Relay::Value)kOff);
	}
}*/

void Kicker::KickBall(){
	printf("Kicking ball...\n");
	firesolenoid->Set(true);
	if (firesolenoid->Get()) {
		printf("firesolenoid = true\n");
	}
}

void Kicker::ReleaseFireSolenoid() {
	firesolenoid->Set(false);
}

void Kicker::RunPeriod(){
	if (ktooth )
	
	}
}
