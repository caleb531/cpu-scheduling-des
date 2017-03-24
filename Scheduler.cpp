/**
 * Scheduler abstract base typename implementation
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
	Process *proc = new Process(procID, event->eventTime);
	procTable.push_back(proc);

	// Determine its next CPU burst length and put it into the readyQueue
	proc->nextCPUBurstLength = CPUBurstRandom(proc->averageCPUBurstLength);
	proc->status = Process::WAITING;
	readyQueue.push(proc);

	schedule(event->eventTime);
}

template <typename ReadyQueue>
void Scheduler<ReadyQueue>::handleCPUCompletion(Event *event) {
	// Find the process that the event is talking about
	int procID = event->procId;
	Process *proc = findProcess(procID);

	// If the process is done with its CPU bursts, terminate it
	if (proc->remainingCPUDuration = 0) {
		proc->status = Process::TERMINATED;
	}
	else {
		// Else determine a random IO burst time and create an io completion event
		srand(time(NULL));
		int ioTime = rand() % 71 + 30;
		proc->IOBurstTime = ioTime;

		Event *newEvent = new Event(Event::IO_COMPLETION, event->eventTime + proc->IOBurstTime, proc->procId);
		eventQueue->push(newEvent);
	}

	isCPUIdle = true;
	schedule(event->eventTime);
}

template <typename ReadyQueue>
void Scheduler<ReadyQueue>::handleIOCompletion(Event *event) {
	// Find the process that the event is talking about
	int procID = event->procId;
	Process *proc = findProcess(procID);

	// Determine its next CPU burst length and put it into the readyQueue
	proc->nextCPUBurstLength = CPUBurstRandom(proc->averageCPUBurstLength);
	proc->status = Process::WAITING;
	readyQueue.push(proc);

	schedule(event->eventTime);
}

template <typename ReadyQueue>
void Scheduler<ReadyQueue>::handleEvent(Event *e) {
	switch (e->eventType) {
		case Event::PROCESS_ARRIVAL:
			handleProcArrival(e);
			break;
		case Event::CPU_COMPLETION:
			handleCPUCompletion(e);
			break;
		case Event::IO_COMPLETION:
			handleIOCompletion(e);
			break;
	}
}
