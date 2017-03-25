/**
 * Scheduler abstract base class definition
 */
#pragma once
#include <deque>
#include <queue>
#include "Process.h"
#include "Event.h"
#include "GenericScheduler.h"
using namespace std;

// Define handy aliases to complex queue types used throughout program
typedef queue<Process*> ProcessQueue;
typedef priority_queue<Process*, deque<Process*>, ProcessComparator> ProcessPriorityQueue;
typedef priority_queue<Event*, deque<Event*>, EventComparator> EventPriorityQueue;

// The Scheduler class should not be instantiated itself; it should instead be
// subclassed, with the following virtual methods implemented
template <typename ReadyQueue>
class Scheduler : public GenericScheduler {

	protected:

		// The list of all processes in the system
		vector<Process*> procTable;
		// A reference to the process event queue; this is supplied when the
		// scheduler is instantiated
		EventPriorityQueue *eventQueue;
		// The queue containing processes in the READY state; each subclass
		// defines the particular type of queue
		ReadyQueue readyQueue;

		// Flag to note whether the CPU is being used or not
		bool isCPUIdle;

	public:

		Scheduler(EventPriorityQueue *eventQueue);

		// Handle various kinds of process events
		void handleProcArrival(Event *event);
		void handleCPUCompletion(Event *event);
		void handleIOCompletion(Event *event);
		void handleEvent(Event *event);

		// The core scheduling algorithm that determines which processes get
		// time on the CPU; this must be defined by each subclass
		virtual void schedule(int currentTime) = 0;

		// Returns a pointer to the process in the procTable as determined by its ID
		//Returns NULL if not found in table
		Process* findProcess(int procID);

};
