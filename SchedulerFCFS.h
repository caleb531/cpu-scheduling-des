/**
 * First-Come-First-Serve (FCFS) scheduler definition
 */
#pragma once
#include <queue>
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
using namespace std;

class SchedulerFCFS : public Scheduler {

	public:

		// The queue containing processes in the READY state
		queue<Process*> readyQueue;

		SchedulerFCFS(priority_queue<Event*> *eventQueue);

		void handleProcArrival(Event *event);
		void handleCPUCompletion(Event *event);
		void handleIOCompletion(Event *event);
		void handleEvent(Event *event);
		void schedule();

};
