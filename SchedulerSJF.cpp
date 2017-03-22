/**
 * Shortest-Job-First (SJF) scheduler implementation
 */
#include <queue>
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
#include "SchedulerSJF.h"
using namespace std;


SchedulerSJF::SchedulerSJF(priority_queue<Event*> *eventQueue) : Scheduler(eventQueue) {
	// Do nothing; the initializer list takes care of everything
}

void SchedulerSJF::handleProcArrival(Event *event) {
	// TODO: handle process arrival event
	schedule();
}
void SchedulerSJF::handleCPUCompletion(Event *event) {
	// TODO: handle CPU completion event
	schedule();
}
void SchedulerSJF::handleIOCompletion(Event *event) {
	// TODO: handle I/O completion event
	schedule();
}
/*void SchedulerSJF::handleEvent(Event *event) {
	// TODO: handle any type of event
}*/

void SchedulerSJF::schedule() {
	// TODO: implement SJF scheduling
}
