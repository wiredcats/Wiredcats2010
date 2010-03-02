#include "WPILib.h"

class Kickertooth {
public:
	DigitalInput *geartooth;
	int count, lastDigSig;
	
	Kickertooth(int channel);
	void RunPeriod();
	void ResetToothCount();
	
	int GetToothCount();
};
