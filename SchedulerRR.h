/**
 * Round-Robin (RR) scheduler definition
 */
#pragma once
#include "Scheduler.h"
using namespace std;

class SchedulerRR : public Scheduler<ProcessQueue> {

	public:

		SchedulerRR(EventPriorityQueue *eventQueue);
		virtual ~SchedulerRR();
		void schedule(int currentTime);

};