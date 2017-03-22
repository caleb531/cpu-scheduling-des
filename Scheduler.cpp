/**
 * Scheduler abstract base class implementation
 */
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
using namespace std;

Scheduler::Scheduler(priority_queue<Event*> *eventQueue) {
	this->eventQueue = eventQueue;
}

Scheduler::handleEvent(Event *e){
	switch(e->eventType){
		case PROCESS_ARRIVAL: 
			handleProcArrival(e);
			break;
		case CPU_COMPLETION:
			handleCPUCompletion(e);
			break;
		case IO_COMPLETION:
			handleIOCompletion(e);
			break;
	}
}
