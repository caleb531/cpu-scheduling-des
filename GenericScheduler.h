/**
 * Scheduler abstract base class definition
 */
#pragma once
#include <deque>
#include <queue>
#include "GenericScheduler.h"
#include "Process.h"
#include "Event.h"
using namespace std;

// Define handy aliases to complex queue types used throughout program
typedef queue<Process*> ProcessQueue;
typedef priority_queue<Process*, deque<Process*>, ProcessComparator> ProcessPriorityQueue;
typedef priority_queue<Event*, deque<Event*>, EventComparator> EventPriorityQueue;

// A generic Scheduler class that does not use templates; this class is useful
// for declaring Scheduler pointers without knowing their template type in
// advance
class GenericScheduler {

	protected:

		// The list of all processes in the system
		vector<Process*> procTable;
		// A reference to the process event queue; this is supplied when the
		// scheduler is instantiated
		EventPriorityQueue *eventQueue;

		// Flag to note whether the CPU is being used or not
		bool isCPUIdle;

	public:

		// Handle any kind of process event
		virtual void handleEvent(Event *event) = 0;

};
