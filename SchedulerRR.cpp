/**
 * Round-Robin (RR) scheduler implementation
 */
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
#include "SchedulerRR.h"
using namespace std;


SchedulerRR::SchedulerRR(EventPriorityQueue *eventQueue, int timeSliceAmount) : Scheduler<ProcessQueue>(eventQueue) {
	// The initializer list takes care of most things
    this->timeSlice = timeSliceAmount;
}

SchedulerRR::~SchedulerRR() {
	// Deallocate queue of ready processes
	while (!readyQueue.empty()) {
		Process *topProc = readyQueue.front();
		readyQueue.pop();
		delete topProc;
	}
}

void SchedulerRR::handleTimerExpiration(Event *exEvent) {
    // If the process is not currently running, don't need to handle it
    if (runningProcess->procId != exEvent->procId){
        return;
    }

    // Ensure that the process knows how much more it needs to do, and set it to wait
    runningProcess->nextCPUBurstLength -= (exEvent->eventTime - runningProcess->burstStartTime);   
    runningProcess->status = Process::WAITING;

    // Then, add it to the end of the readyQueue
    readyQueue.push(runningProcess);

    isCPUIdle = true;
    schedule(exEvent->eventTime);
}

void SchedulerRR::handleEvent(Event *event) {
	// Assume the scheduler run ends when the very last event has been emitted
	totalSchedulerTime = event->eventTime;
	switch (event->eventType) {
		case Event::PROCESS_ARRIVAL:
			handleProcArrival(event);
			break;
		case Event::CPU_COMPLETION:
			handleCPUCompletion(event);
			break;
		case Event::IO_COMPLETION:
			handleIOCompletion(event);
			break;
		case Event::TIMER_EXPIRATION:
            handleTimerExpiration(event);
            break;
	}
}

void SchedulerRR::schedule(int currentTime) {
	if (isCPUIdle && !readyQueue.empty()) {
		// If the CPU is idle, grab the next process from readyQueue and set it to run
		Process *runningProc = readyQueue.front();
		readyQueue.pop();
		runningProc->status = Process::RUNNING;
		runningProc->burstStartTime = currentTime;
		runningProcess = runningProc;
		isCPUIdle = false;

        // If the process will time out before completing its CPU burst, don't create a CPU completion event. Likewise vice-versa.
        Event *newEvent;
        if (timeSlice < runningProc->nextCPUBurstLength) {
            newEvent = new Event(Event::TIMER_EXPIRATION, currentTime + timeSlice, runningProc->procId);
        } else {
            newEvent = new Event(Event::CPU_COMPLETION, currentTime + runningProc->nextCPUBurstLength, runningProc->procId);
        }

		eventQueue->push(newEvent);
	}
}