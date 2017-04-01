/**
 * Preemptive Shortest-Job-First (PSJF) scheduler implementation
 */
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
#include "SchedulerPSJF.h"
using namespace std;


SchedulerPSJF::SchedulerPSJF(EventPriorityQueue *eventQueue) : Scheduler<ProcessPriorityQueue>(eventQueue) {
	// Do nothing; the initializer list takes care of everything
}

SchedulerPSJF::~SchedulerPSJF() {
	// Deallocate priority queue of ready processes
	while (!readyQueue.empty()) {
		Process *topProc = readyQueue.top();
		readyQueue.pop();
		delete topProc;
	}
}

void SchedulerPSJF::schedule(int currentTime) {
	if (isCPUIdle && !readyQueue.empty()) {
		// If the CPU is idle, grab the next process from readyQueue and set it
		// to run
		Process *runningProc = readyQueue.top();
		readyQueue.pop();
		runningProc->status = Process::RUNNING;
        runningProc->burstStartTime = currentTime;
        runningProcess = runningProc;
		isCPUIdle = false;

		Event *newEvent = new Event(Event::CPU_COMPLETION, currentTime + runningProc->nextCPUBurstLength, runningProc->procId);
		eventQueue->push(newEvent);
	}
    else if (!readyQueue.empty()) {
        // Check if the next process is shorter than the currently running process,
        // then preempt that process if so
        Process *nextProc = readyQueue.top();
        if (nextProc->remainingCPUDuration < runningProcess->remainingCPUDuration) {
            readyQueue.pop();

            // Update the runningProcess's burstLength time, and add it to the readyQueue
            runningProcess->status = Process::WAITING;
            runningProcess->nextCPUBurstLength -= (currentTime - runningProcess->burstStartTime);
            readyQueue.push(runningProcess);

            // Grab the shorter nextProc and set it to run
            nextProc->status = Process::RUNNING;
            runningProcess = nextProc;
            Event *newEvent = new Event(Event::CPU_COMPLETION, currentTime + nextProc->nextCPUBurstLength, nextProc->procId);
		    eventQueue->push(newEvent);
        }
    }
}
