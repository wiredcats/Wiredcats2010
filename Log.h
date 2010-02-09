#ifndef LOG_H_
#define LOG_H_

#include <fstream>
#include <sstream>
#include "Timer.h"

class Log {
public:
	ofstream lfr;
	char* mode;
	Timer *timer;
	
	Log(char* path);
	void addLine(char* line);
	void closeLog();
	
	void startTimer();
	void resetTimer();
	
	void setMode(char* newMode);
};

#endif
