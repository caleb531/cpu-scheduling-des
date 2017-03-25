/**
 * Generic (template-less) scheduler base class definition
 */
#pragma once
#include "Event.h"
using namespace std;

// A generic Scheduler class that does not use templates; this class is useful
// for declaring Scheduler pointers without knowing their template type in
// advance
class GenericScheduler {

	public:

		// Handle any kind of process event
		virtual void handleEvent(Event *event) = 0;

};
