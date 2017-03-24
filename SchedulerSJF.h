/**
 * Shortest-Job-First (SJF) scheduler definition
 */
#pragma once
#include <queue>
#include "Scheduler.h"
using namespace std;

class SchedulerSJF : public Scheduler<ProcessPriorityQueue> {

	public:

		SchedulerSJF(EventPriorityQueue *eventQueue);
		void schedule(int currentTime);

};
