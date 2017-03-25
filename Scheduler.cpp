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
Scheduler<ReadyQueue>::~Scheduler() {
	// Deallocate all remaining processes in process table
	for (int i = 0; i < procTable.size(); i++) {
		delete procTable[i];
	}
	// Delete references to deallocated memory
	procTable.clear();
	eventQueue = NULL;
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
void Scheduler<ReadyQueue>::handleProcArrival(Event *arrivalEvent) {
	int procID = arrivalEvent->procId;

	// Create a process and put in in the process table
	Process *newProc = new Process(procID, arrivalEvent->eventTime);
	procTable.push_back(newProc);

	// Determine its next CPU burst length and put it into the readyQueue
	newProc->nextCPUBurstLength = CPUBurstRandom(newProc->averageCPUBurstLength);
	newProc->status = Process::WAITING;
	readyQueue.push(newProc);

	schedule(arrivalEvent->eventTime);
}

template <typename ReadyQueue>
void Scheduler<ReadyQueue>::handleCPUCompletion(Event *cpuEvent) {
	// Find the process that the event is talking about
	Process *eventProc = findProcess(cpuEvent->procId);

	if (eventProc->remainingCPUDuration == 0) {
		// If the process is completely finished with its work, terminate it
		eventProc->status = Process::TERMINATED;
		eventProc->finishTime = cpuEvent->eventTime;
	} else {
		// Ensure that the process knows how much more it needs to do
		eventProc->remainingCPUDuration -= eventProc->nextCPUBurstLength;
		// Prepare an I/O completion event to run next
		srand(time(NULL));
		eventProc->IOBurstTime = rand() % 71 + 30;
		Event *ioEvent = new Event(Event::IO_COMPLETION, cpuEvent->eventTime + eventProc->IOBurstTime, eventProc->procId);
		eventQueue->push(ioEvent);
	}

	isCPUIdle = true;
	schedule(cpuEvent->eventTime);
}

template <typename ReadyQueue>
void Scheduler<ReadyQueue>::handleIOCompletion(Event *ioEvent) {
	// Find the process that the event is talking about
	Process *eventProc = findProcess(ioEvent->procId);

	eventProc->totalIODuration += eventProc->IOBurstTime;
	// Determine its next CPU burst length and put it into the readyQueue
	eventProc->nextCPUBurstLength = CPUBurstRandom(eventProc->averageCPUBurstLength);
	eventProc->status = Process::WAITING;
	readyQueue.push(eventProc);

	schedule(ioEvent->eventTime);
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
