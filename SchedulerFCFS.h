/**
 * First-Come-First-Serve (FCFS) scheduler definition
 */
#pragma once
#include <queue>
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
using namespace std;

class SchedulerFCFS : public Scheduler<ProcessQueue> {

	public:

		SchedulerFCFS(EventPriorityQueue *eventQueue);
		void schedule(int currentTime);

};
