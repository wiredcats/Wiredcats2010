#include "Kicker.h" 

Kicker::Kicker():
spike(SPIKE_NUM) {
	encoder = new Encoder(ENCODER_CHANNEL_1,ENCODER_CHANNEL_2);
	servo = new Servo(2);
	compressor = new Compressor(1,1);
	solenoid = new Solenoid(8, 1);
}

void Kicker::StartCompressor() {
	compressor->Start();
}

void Kicker::MoveKicker(KickerSetting ks) {
	switch(ks) {
	case kWinchUp:
		servo->Set(0.2);
		spike.Set(Relay::kReverse);
		break;
	case kWinchStop:
		spike.Set(Relay::kOff);
		break;
	default:
		// Oh nose
		break;
	}
}

void Kicker::LockServo() {
	servo->Set(0.1);
}

void Kicker::UnlockServo() {
	servo->Set(0.9);
}

float Kicker::GetEncoder() {
	return encoder->Get();
}

void Kicker::RunBackdrive() {
	spike.Set(Relay::kForward);
	Wait(2.0);
	spike.Set(Relay::kOff);
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
	solenoid->Set(true);
	if (solenoid->Get()) {
		printf("solenoid = true\n");
	}
}

void Kicker::ReleaseSolenoid() {
	solenoid->Set(false);
}
