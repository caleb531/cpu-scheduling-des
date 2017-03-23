/**
 * Process implementation
 * See the corresponding header file for descriptions of each function
 */
#include <cstdlib>
#include <ctime>
#include "Process.h"
using namespace std;

Process::Process(int procId, int startTime) {
	this->procId = procId;
	this->startTime = startTime;

	srand(time(NULL));
	this->totalCPUDuration = rand() % 59000 + 1000;
	this->averageCPUBurstLength = rand() % 96 + 5;

	this->remainingCPUDuration = totalCPUDuration;
}

bool operator <(const Process &a, const Process &b) {
	return a.totalCPUDuration < b.totalCPUDuration;
}
bool operator >(const Process &a, const Process &b) {
	return a.totalCPUDuration > b.totalCPUDuration;
}
bool operator ==(const Process &a, const Process &b) {
	return a.totalCPUDuration == b.totalCPUDuration;
}
