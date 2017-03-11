/**
 * Scheduler abstract base class definition
 */
#pragma once
#include <queue>
#include "Process.h"
#include "Event.h"
using namespace std;

// The Scheduler class should not be instantiated itself; it should instead be
// subclassed, with the following virtual methods implemented
class Scheduler {

	protected:

		// The list of all processes in the system
		vector<Process> procTable;
		// A reference to the process event queue; this is supplied when the
		// scheduler is instantiated
		priority_queue<Event*> *eventQueue;

	public:

		Scheduler(priority_queue<Event*> *eventQueue);

		// Add the given process to the queue

		// Handle various kinds of process events
		virtual void handleProcArrival(Event *event) = 0;
		virtual void handleCPUCompletion(Event *event) = 0;
		virtual void handleIOCompletion(Event *event) = 0;
		virtual void handleEvent(Event *event) = 0;

		// The core scheduling algorithm that determines which processes get
		// time on the CPU; this must be defined by each subclass
		virtual void schedule() = 0;

};
