/**
 * Process implementation
 * See the corresponding header file for descriptions of each function
 */
#include <cstdlib>
#include <ctime>
#include "Process.h"
using namespace std;

Process::Process(int procId, int arrivalTime) {
	this->procId = procId;
	this->arrivalTime = arrivalTime;

	srand(time(NULL));
	this->totalCPUDuration = rand() % 59000 + 1000;
	this->averageCPUBurstLength = rand() % 96 + 5;
	this->totalIODuration = 0;

	this->remainingCPUDuration = totalCPUDuration;
}

bool ProcessComparator::operator ()(Process *a, Process *b) {
	// The STL priority_queue considers the greatest numeric value to be the
	// highest priority, but we want the other way around
	return a->totalCPUDuration > b->totalCPUDuration;
}
