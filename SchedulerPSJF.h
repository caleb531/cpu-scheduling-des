/**
 * Priority Shortest-Job-First (PSJF) scheduler definition
 */
#pragma once
#include "Scheduler.h"
using namespace std;

class SchedulerPSJF : public Scheduler<ProcessPriorityQueue> {

	public:

		SchedulerPSJF(EventPriorityQueue *eventQueue);
		virtual ~SchedulerPSJF();
		void schedule(int currentTime);

};
