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

void SchedulerRR::handleTimerExpiration(Event *exEvent) {

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
	//TODO: Implement
}