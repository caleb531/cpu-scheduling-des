/**
 * Scheduler abstract base class definition
 */
#pragma once
#include <deque>
#include <queue>
#include <string>
#include "Process.h"
#include "Event.h"
#include "SchedulerPointer.h"
using namespace std;

// Define handy aliases to complex queue types used throughout program
typedef queue<Process*> ProcessQueue;
typedef priority_queue<Process*, deque<Process*>, ProcessComparator> ProcessPriorityQueue;
typedef priority_queue<Event*, deque<Event*>, EventComparator> EventPriorityQueue;

// The Scheduler class should not be instantiated itself; it should instead be
// subclassed, with the following virtual methods implemented
template <typename ReadyQueue>
class Scheduler : public SchedulerPointer {

	protected:

		// Conversion factor for milliseconds to seconds
		const float MS_TO_S = 1000.0;

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

		// The total time the scheduler is running
		int totalSchedulerTime;

	public:

		Scheduler(EventPriorityQueue *eventQueue);
		virtual ~Scheduler();

		// Handle various kinds of process events
		void handleProcArrival(Event *arrivalEvent);
		void handleCPUCompletion(Event *cpuEvent);
		void handleIOCompletion(Event *ioEvent);
		void handleEvent(Event *event);

		// The core scheduling algorithm that determines which processes get
		// time on the CPU; this must be defined by each subclass
		virtual void schedule(int currentTime) = 0;

		// Returns a pointer to the process in the procTable as determined by its ID
		//Returns NULL if not found in table
		Process* findProcess(int procID);

		// Print any particular time metric (e.g. process turnaround time)
		void printTimeStat(string statLabel, int statTime);
		void printSubStat(string statLabel, int statTime);

		// Print the process and scheduler statistics
		void printStats();

};
