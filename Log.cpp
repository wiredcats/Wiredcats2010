#include "Log.h"

using namespace std;

Log::Log(char* path) {
	lfr.open(path);
}

void Log::addLine(char* line) {
	lfr << line << endl;
}

void Log::closeLog() {
	lfr.close();
}
