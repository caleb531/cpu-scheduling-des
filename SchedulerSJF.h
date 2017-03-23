/**
 * Shortest-Job-First (SJF) scheduler definition
 */
#pragma once
#include <queue>
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
using namespace std;

class SchedulerSJF : public Scheduler<priority_queue<Process*>> {

	public:

		SchedulerSJF(priority_queue<Event> *eventQueue);
		void schedule(int currentTime);

};
