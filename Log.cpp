#include "Log.h"

using namespace std;

string formatTimer(double time) {
	stringstream out;
	
	int minutes = (int)time / 60;
	int seconds = (int)time - (60 * minutes);
	
	out << minutes + ":" + seconds;
	return out.str();
}

Log::Log(char* path) {
	lfr.open(path);
	timer = new Timer();
}

void Log::addLine(char* line) {
	lfr << "[" << formatTimer(timer->Get()) << " - " << mode << "] " << line << endl;
}

void Log::closeLog() {
	lfr.close();
}

void Log::startTimer() {
	timer->Start();
}

void Log::resetTimer() {
	timer->Stop();
	timer->Reset();
}

void Log::setMode(char* newMode) {
	mode = newMode;
}

int Log::readTextNumber(char* path){
	string line;
	int number;
	
	infile.open(path);
	getline(infile,line);
	
	stringstream ssNum(line);
	ssNum >> number;

	temp.open("temp.txt");
	while(getline(infile,line)){
			temp << line << "\n";
		}
	temp.close();
	infile.close();
	
	remove(path);
	rename("temp.txt",path);
	remove("temp.txt");
	
	return number;
}
