/**
 * First-Come-First-Serve (FCFS) scheduler implementation
 */
#include <queue>
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
#include "SchedulerFCFS.h"
#include "random.h"
using namespace std;


SchedulerFCFS::SchedulerFCFS(priority_queue<Event*> *eventQueue) : Scheduler(eventQueue) {
	// Do nothing; the initializer list takes care of everything
}

void SchedulerFCFS::handleProcArrival(Event *event) {
	int procID = event->procId;

	Process *proc = new Process(procID, event->eventTime);
	procTable.push_back(proc);

	proc->nextCPUBurstLength = CPUBurstRandom(proc->averageCPUBurstLength);
	readyQueue.push(proc);

	schedule();
}
void SchedulerFCFS::handleCPUCompletion(Event *event) {
	// TODO: handle CPU completion event
	schedule();
}
void SchedulerFCFS::handleIOCompletion(Event *event) {
	// TODO: handle I/O completion event
	schedule();
}
/*void SchedulerFCFS::handleEvent(Event *event) {
	// TODO: handle any type of event
}*/

void SchedulerFCFS::schedule() {
	if(isCPUIdle){
		Process *proc = readyQueue.front();
		readyQueue.pop();
		proc->status = Process::RUNNING;

		//TODO: Check time for event to finish
		Event *newEvent = new Event(Event::CPU_COMPLETION, proc->nextCPUBurstLength, proc->procId);
		
		eventQueue->push(newEvent);
	}
}
