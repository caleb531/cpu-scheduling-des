/**
 * First-Come-First-Serve (FCFS) scheduler implementation
 */
#include <queue>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
#include "SchedulerFCFS.h"
#include "random.h"
using namespace std;


SchedulerFCFS::SchedulerFCFS(priority_queue<Event> *eventQueue) : Scheduler(eventQueue) {
	// Do nothing; the initializer list takes care of everything
}

void SchedulerFCFS::handleProcArrival(Event *event) {
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

void SchedulerFCFS::handleCPUCompletion(Event *event) {
	// Find the process that the event is talking about
	int procID = event->procId;
	Process *proc = findProcess(procID);

	// If the process is done with its CPU bursts, terminate it
	if (proc->remainingCPUDuration = 0){
		proc->status = Process::TERMINATED;
	}
	else {
		// Else determine a random IO burst time and create an io completion event
		srand(time(NULL));
		int ioTime = rand() % 71 + 30;
		proc->IOBurstTime = ioTime;
		
		Event *newEvent = new Event(Event::IO_COMPLETION, event->eventTime + proc->IOBurstTime, proc->procId);
		eventQueue->push(*newEvent);
	}

	isCPUIdle = true;
	schedule(event->eventTime);
}
void SchedulerFCFS::handleIOCompletion(Event *event) {
	// Find the process that the event is talking about
	int procID = event->procId;
	Process *proc = findProcess(procID);

	// Determine its next CPU burst length and put it into the readyQueue
	proc->nextCPUBurstLength = CPUBurstRandom(proc->averageCPUBurstLength);
	proc->status = Process::WAITING;
	readyQueue.push(proc);

	schedule(event->eventTime);
}

void SchedulerFCFS::schedule(int currentTime) {
	if(isCPUIdle && !readyQueue.empty()){
		// If the CPU is idle, grab the next process from readyQueue and set it to run
		Process *proc = readyQueue.front();
		readyQueue.pop();
		proc->status = Process::RUNNING;

		Event *newEvent = new Event(Event::CPU_COMPLETION, currentTime + proc->nextCPUBurstLength, proc->procId);
		eventQueue->push(*newEvent);
	}
}
