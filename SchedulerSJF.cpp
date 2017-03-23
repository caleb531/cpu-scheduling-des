/**
 * Shortest-Job-First (SJF) scheduler implementation
 */
#include <queue>
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
#include "SchedulerSJF.h"
using namespace std;


SchedulerSJF::SchedulerSJF(EventPriorityQueue *eventQueue) : Scheduler<ProcessPriorityQueue>(eventQueue) {
	// Do nothing; the initializer list takes care of everything
}

void SchedulerSJF::schedule(int currentTime) {
	// TODO: implement SJF scheduling
}
