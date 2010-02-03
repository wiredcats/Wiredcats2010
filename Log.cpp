#include "Log.h"

using namespace std;

Log::Log(char* path) {
	lfr.open(path);
	
	buff = cerr.rdbuf();
	cerr.rdbuf(lfr.rdbuf());
}

void Log::addLine(char* line) {
	cerr << line << endl;
}

void Log::closeLog() {
	cerr.rdbuf(buff);
	lfr.close();
}
