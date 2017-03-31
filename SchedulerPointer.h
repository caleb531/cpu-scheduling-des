/**
 * Parent class designed to allow Schedulers to be declared as pointers
 */
#pragma once
#include "Event.h"
using namespace std;

// A parent class for Schedulers that does not use templates; this class is
// useful for declaring Scheduler pointers without knowing their template type
// in advance
class SchedulerPointer {

	public:

		// Handle any kind of process event
		virtual void handleEvent(Event *event) = 0;

		// Print the process and scheduler statistics
		virtual void printStats() = 0;

};
