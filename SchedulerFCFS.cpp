/**
 * First-Come-First-Serve (FCFS) scheduler implementation
 */
#include <queue>
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
#include "SchedulerFCFS.h"
using namespace std;


SchedulerFCFS::SchedulerFCFS(priority_queue<Event*> *eventQueue) : Scheduler(eventQueue) {
	// Do nothing; the initializer list takes care of everything
}

void SchedulerFCFS::handleProcArrival(Event *event) {
	// TODO: handle process arrival event
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
void SchedulerFCFS::handleEvent(Event *event) {
	// TODO: handle any type of event
}

void SchedulerFCFS::schedule() {
	// TODO: implement FCFS scheduling
}
