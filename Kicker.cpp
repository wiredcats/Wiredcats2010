#include "Kicker.h" 

Kicker::Kicker():
winch(SPIKE_NUM) {
	encoder = new Encoder(ENCODER_CHANNEL_1,ENCODER_CHANNEL_2);
	servo = new Servo(1,1);
	compressor = new Compressor(1,1);
	firesolenoid = new Solenoid(8,1);
	//dogsolenoid = new Solenoid(8, 1);
	
	backdriveEnabled = false;
}

void Kicker::StartCompressor() {
	compressor->Start();
}

void Kicker::MoveKicker(KickerSetting ks) {
	switch(ks) {
	case kWinchUp:
		servo->Set(0.2);
		winch.Set(Relay::kReverse);
		break;
	case kWinchStop:
		if (!backdriveEnabled)
			winch.Set(Relay::kOff);
		break;
	default:
		// Oh nose
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
