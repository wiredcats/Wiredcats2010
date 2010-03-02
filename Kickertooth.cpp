#include "Kickertooth.h"

Kickertooth::Kickertooth(int channel) {
	geartooth = new DigitalInput(channel);
}

void Kickertooth::RunPeriod() {
	if (geartooth->Get() == 1 && lastDigSig == 0) {
		count++;
	}
	
	lastDigSig = geartooth->Get();
}

void Kickertooth::ResetToothCount() {
	count = 0;
}

int Kickertooth::GetToothCount() {
	return count;
}
