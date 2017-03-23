/**
 * Shortest-Job-First (SJF) scheduler definition
 */
#pragma once
#include <deque>
#include <queue>
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
using namespace std;

class SchedulerSJF : public Scheduler< priority_queue< Process*, deque<Process*>, ProcessComparator > > {

	public:

		SchedulerSJF(priority_queue< Event*, deque<Event*>, EventComparator > *eventQueue);
		void schedule(int currentTime);

};
