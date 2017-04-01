/**
 * Shortest-Job-First (SJF) scheduler implementation
 */
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
#include "SchedulerSJF.h"
using namespace std;


SchedulerSJF::SchedulerSJF(EventPriorityQueue *eventQueue) : Scheduler<ProcessPriorityQueue>(eventQueue) {
	// Do nothing; the initializer list takes care of everything
}

SchedulerSJF::~SchedulerSJF() {
	// Deallocate priority queue of ready processes
	while (!readyQueue.empty()) {
		Process *topProc = readyQueue.top();
		readyQueue.pop();
		delete topProc;
	}
}

void SchedulerSJF::schedule(int currentTime) {
	if (isCPUIdle && !readyQueue.empty()) {
		// If the CPU is idle, grab the next process from readyQueue and set it
		// to run
		Process *runningProc = readyQueue.top();
		readyQueue.pop();
		runningProc->status = Process::RUNNING;
		runningProcess = runningProc;
		isCPUIdle = false;

		Event *newEvent = new Event(Event::CPU_COMPLETION, currentTime + runningProc->nextCPUBurstLength, runningProc->procId);
		eventQueue->push(newEvent);
	}
}
