/**
 * Scheduler abstract base class implementation
 */
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <iostream>
#include <string>
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
	this->totalSchedulerTime = 0;
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

	if (eventProc->remainingCPUDuration <= 0) {
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
	}
}

template <typename ReadyQueue>
void Scheduler<ReadyQueue>::printTimeStat(string statLabel, int statTime) {
	cout << statLabel << ": " << ((float)statTime / MS_TO_S) << "s" << endl;
}

template <typename ReadyQueue>
void Scheduler<ReadyQueue>::printSubStat(string statLabel, int statTime) {
	cout << "    ";
	printTimeStat(statLabel, statTime);
}

template <typename ReadyQueue>
void Scheduler<ReadyQueue>::printStats() {
	// Keep running sums of various metrics for computing the averages later
	int turnaroundTimeSum = 0;
	int waitingTimeSum = 0;
	int serviceTimeSum = 0;
	for (int i = 0; i < procTable.size(); i++) {
		cout << "Process " << procTable[i]->procId << ":" << endl;

		printSubStat("Arrival", procTable[i]->getArrivalTime());
		printSubStat("Finish", procTable[i]->getFinishTime());

		int serviceTime = procTable[i]->getServiceTime();
		printSubStat("Service", serviceTime);
		serviceTimeSum += serviceTime;

		printSubStat("I/O", procTable[i]->getIOTime());

		int turnaroundTime = procTable[i]->getTurnaroundTime();
		printSubStat("Turnaround", turnaroundTime);
		turnaroundTimeSum += turnaroundTime;

		int waitingTime = procTable[i]->getWaitingTime();
		printSubStat("Waiting", waitingTime);
		waitingTimeSum += waitingTime;

	}
	cout << "CPU Utilization: " <<
		(100 * serviceTimeSum / totalSchedulerTime) << '%' << endl;
	printTimeStat("Avg Turnaround Time",
		(float)turnaroundTimeSum / (float)procTable.size());
	printTimeStat("Avg Waiting Time",
		(float)waitingTimeSum / (float)procTable.size());
}
