/**
 * Process implementation
 * See the corresponding header file for descriptions of each function
 */
#include "Process.h"
using namespace std;

Process::Process(int procId, int startTime) {
	this->procId = procId;
	this->startTime = startTime;

	// TODO: Randomly determine totalCpuDuration, averageCpuBurstLength

	this->remainingCPUDuration = totalCPUDuration;
}
