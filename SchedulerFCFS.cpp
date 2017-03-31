/**
 * First-Come-First-Serve (FCFS) scheduler implementation
 */
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
#include "SchedulerFCFS.h"
using namespace std;


SchedulerFCFS::SchedulerFCFS(EventPriorityQueue *eventQueue) : Scheduler<ProcessQueue>(eventQueue) {
	// Do nothing; the initializer list takes care of everything
}

SchedulerFCFS::~SchedulerFCFS() {
	// Deallocate queue of ready processes
	while (!readyQueue.empty()) {
		Process *topProc = readyQueue.front();
		readyQueue.pop();
		delete topProc;
	}
}

void SchedulerFCFS::schedule(int currentTime) {
	if (isCPUIdle && !readyQueue.empty()) {
		// If the CPU is idle, grab the next process from readyQueue and set it to run
		Process *runningProc = readyQueue.front();
		readyQueue.pop();
		runningProc->status = Process::RUNNING;
		isCPUIdle = false;

		Event *newEvent = new Event(Event::CPU_COMPLETION, currentTime + runningProc->nextCPUBurstLength, runningProc->procId);
		eventQueue->push(newEvent);
	}
}
