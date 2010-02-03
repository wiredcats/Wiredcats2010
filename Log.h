#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ostream>

class Log {
public:
	ofstream lfr;
	streambuf *buff;
	
	Log(char* path);
	void addLine(char* line);
	void closeLog();
};

#endif
