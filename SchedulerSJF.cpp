/**
 * Shortest-Job-First (SJF) scheduler implementation
 */
#include <deque>
#include <queue>
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
#include "SchedulerSJF.h"
using namespace std;


SchedulerSJF::SchedulerSJF(priority_queue< Event*, deque<Event*>, EventComparator > *eventQueue) : Scheduler< priority_queue< Process*, deque<Process*>, ProcessComparator > >(eventQueue) {
	// Do nothing; the initializer list takes care of everything
}

void SchedulerSJF::schedule(int currentTime) {
	// TODO: implement SJF scheduling
}
