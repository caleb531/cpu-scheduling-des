/**
 * First-Come-First-Serve (FCFS) scheduler definition
 */
#pragma once
#include <deque>
#include <queue>
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
using namespace std;

class SchedulerFCFS : public Scheduler< queue<Process*> > {

	public:

		SchedulerFCFS(priority_queue< Event*, deque<Event*>, EventComparator > *eventQueue);
		void schedule(int currentTime);

};
