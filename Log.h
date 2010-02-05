#ifndef LOG_H_
#define LOG_H_

#include <fstream>

class Log {
public:
	ofstream lfr;
	
	Log(char* path);
	void addLine(char* line);
	void closeLog();
};

#endif
