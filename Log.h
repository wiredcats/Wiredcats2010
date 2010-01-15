#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>

class Log {
public:
	FILE* log;
	
	Log(char* path);
	void addLine(char* line);
	void close();
};

#endif
