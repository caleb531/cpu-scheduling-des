/**
 * Round-Robin (RR) scheduler implementation
 */
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
#include "SchedulerRR.h"
using namespace std;


SchedulerRR::SchedulerRR(EventPriorityQueue *eventQueue) : Scheduler<ProcessQueue>(eventQueue) {
	// Do nothing; the initializer list takes care of everything
}

SchedulerRR::~SchedulerRR() {
	// Deallocate queue of ready processes
	while (!readyQueue.empty()) {
		Process *topProc = readyQueue.front();
		readyQueue.pop();
		delete topProc;
	}
}

void SchedulerRR::schedule(int currentTime) {
	//TODO: Implement
}