#include "Kicker.h" 

Kicker::Kicker() {
	encoder = new Encoder(ENCODER_CHANNEL_1,ENCODER_CHANNEL_2);
	spike = new Relay(SPIKE_NUM);
	compressor = new Compressor(1,1);
	compressor -> Start();
}

void Kicker::ResetEncoder() {
	encoder->Reset();
}

void Kicker::GoToLowGear() {
	if ((encoder->Get()) <= LOW_GEAR_DIST){
		spike->Set((Relay::Value)kOn);
	} else {
		spike->Set((Relay::Value)kOff);
	}
}

void Kicker::GoToMidGear() {
	if ((encoder->Get()) <= MID_GEAR_DIST){
		spike->Set((Relay::Value)kOn);
	} else {
		spike->Set((Relay::Value)kOff);
	}
}

void Kicker::GoToHighGear() {
	if ((encoder->Get()) <= HIGH_GEAR_DIST){
		spike->Set((Relay::Value)kOn);
	} else {
		spike->Set((Relay::Value)kOff);
	}
}
