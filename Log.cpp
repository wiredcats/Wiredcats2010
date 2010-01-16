#include "Log.h"

Log::Log(char* path) {
	/*log = fopen(path, "w");
	fwrite("Test test test", 1, sizeof("Test test test"), log);
	if (log == NULL) {
		printf("ERROR WRITING LOG!\n");
	}*/
	
	lfr.open(path);
}

void Log::addLine(char* line) {
	lfr << line << "\n";
}

void Log::closeLog() {
	lfr.close();
}
