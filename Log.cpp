#include "Log.h"

Log::Log(char* path) {
	log = fopen(path, "w");
	if (log == NULL) {
		printf("ERROR WRITING LOG!\n");
	}
}

void Log::addLine(char* line) {
	fputs(line, log);
}

void Log::close() {
	fclose(log);
}
