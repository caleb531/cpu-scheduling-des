/**
 * First-Come-First-Serve (FCFS) scheduler implementation
 */
#include <queue>
#include <cstdlib>
#include <iostream>
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
#include "SchedulerFCFS.h"
using namespace std;


SchedulerFCFS::SchedulerFCFS(priority_queue<Event> *eventQueue) : Scheduler< queue<Process*> >(eventQueue) {
	// Do nothing; the initializer list takes care of everything
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
