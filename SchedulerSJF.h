/**
 * Shortest-Job-First (SJF) scheduler definition
 */
#pragma once
#include <queue>
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
using namespace std;

class SchedulerSJF : public Scheduler {

	public:

		// The queue containing processes in the READY state
		priority_queue<Process*> readyQueue;

		SchedulerSJF(priority_queue<Event*> *eventQueue);

		void handleProcArrival(Event *event);
		void handleCPUCompletion(Event *event);
		void handleIOCompletion(Event *event);
		void handleEvent(Event *event);
		void schedule();

};
