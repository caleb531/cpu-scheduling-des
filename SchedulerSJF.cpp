/**
 * Shortest-Job-First (SJF) scheduler implementation
 */
#include <queue>
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
#include "SchedulerSJF.h"
using namespace std;


SchedulerSJF::SchedulerSJF(priority_queue<Event> *eventQueue) : Scheduler<priority_queue<Process*>>(eventQueue) {
	// Do nothing; the initializer list takes care of everything
}

void SchedulerSJF::schedule(int currentTime) {
	// TODO: implement SJF scheduling
}
