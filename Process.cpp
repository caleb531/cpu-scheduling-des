/* Implementation of process class */

#include "Process.h"

using namespace std;

Process::Process(int processID, int startTime) {
	this->processID = processID;
	this->startTime = startTime;

	// TODO: Randomly determine totalCpuDuration, averageCpuBurstLength

	this->remainingCPUDuration = totalCPUDuration;
}
