/**
 * Round-Robin (RR) scheduler definition
 */
#pragma once
#include "Scheduler.h"
using namespace std;

class SchedulerRR : public Scheduler<ProcessQueue> {

	private:
		// Amount of time spent per process before switching
		int timeSlice;

	public:

		SchedulerRR(EventPriorityQueue *eventQueue, int timeSliceAmount);
		virtual ~SchedulerRR();
		
		// Handle what to do when timer expires
		void handleTimerExpiration(Event *exEvent);

		void handleEvent(Event *event);
		void schedule(int currentTime);

};