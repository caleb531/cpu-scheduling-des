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
		
		// Handle what to do when timer expires
		void handleTimerExpiration(Event *exEvent);

		void handleEvent(Event *event);
		void schedule(int currentTime);

};