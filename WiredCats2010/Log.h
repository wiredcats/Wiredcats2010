#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include <iostream>
#include <fstream>

class Log {
public:
	ofstream lfr;
	
	Log(char* path);
	void addLine(char* line);
	void closeLog();
};

#endif
