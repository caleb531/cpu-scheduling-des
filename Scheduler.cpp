/**
 * Scheduler abstract base class implementation
 */
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
using namespace std;

Scheduler::Scheduler(priority_queue<Event*> *eventQueue) {
	this->eventQueue = eventQueue;
	this->isCPUIdle = true;
}

void Scheduler::handleEvent(Event *e){
	switch(e->eventType){
		case Event::PROCESS_ARRIVAL: 
			handleProcArrival(e);
			break;
		case Event::CPU_COMPLETION:
			handleCPUCompletion(e);
			break;
		case Event::IO_COMPLETION:
			handleIOCompletion(e);
			break;
	}
}
