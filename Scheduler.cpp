/**
 * Scheduler abstract base class implementation
 */
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <queue>
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
#include "random.h"
using namespace std;

template class Scheduler<ProcessQueue>;
template class Scheduler<ProcessPriorityQueue>;

template <typename ReadyQueue>
Scheduler<ReadyQueue>::Scheduler(EventPriorityQueue *eventQueue) {
	this->eventQueue = eventQueue;
	this->isCPUIdle = true;
}

template <typename ReadyQueue>
Process* Scheduler<ReadyQueue>::findProcess(int procID) {
	for (int i = 0; i < procTable.size(); i++) {
		if (procTable[i]->procId == procID) {
			return procTable[i];
		}
	}

	return NULL;
}

template <typename ReadyQueue>
void Scheduler<ReadyQueue>::handleProcArrival(Event *event) {
	int procID = event->procId;

	// Create a process and put in in the process table
	Process *newProc = new Process(procID, event->eventTime);
	procTable.push_back(newProc);

	// Determine its next CPU burst length and put it into the readyQueue
	newProc->nextCPUBurstLength = CPUBurstRandom(newProc->averageCPUBurstLength);
	newProc->status = Process::WAITING;
	readyQueue.push(newProc);

	schedule(event->eventTime);
}

template <typename ReadyQueue>
void Scheduler<ReadyQueue>::handleCPUCompletion(Event *event) {
	// Find the process that the event is talking about
	Process *eventProc = findProcess(event->procId);

	// If the process is done with its CPU bursts, terminate it
	if (eventProc->remainingCPUDuration == 0) {
		eventProc->status = Process::TERMINATED;
	}
	else {
		// Else determine a random IO burst time and create an io completion event
		srand(time(NULL));
		int ioTime = rand() % 71 + 30;
		eventProc->IOBurstTime = ioTime;

		Event *newEvent = new Event(Event::IO_COMPLETION, event->eventTime + eventProc->IOBurstTime, eventProc->procId);
		eventQueue->push(newEvent);
	}

	isCPUIdle = true;
	schedule(event->eventTime);
}

template <typename ReadyQueue>
void Scheduler<ReadyQueue>::handleIOCompletion(Event *event) {
	// Find the process that the event is talking about
	Process *eventProc = findProcess(event->procId);

	// Determine its next CPU burst length and put it into the readyQueue
	eventProc->nextCPUBurstLength = CPUBurstRandom(eventProc->averageCPUBurstLength);
	eventProc->status = Process::WAITING;
	readyQueue.push(eventProc);

	schedule(event->eventTime);
}

template <typename ReadyQueue>
void Scheduler<ReadyQueue>::handleEvent(Event *event) {
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
	}
}
