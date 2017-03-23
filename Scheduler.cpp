/**
 * Scheduler abstract base class implementation
 */
#include <cstddef>
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"
using namespace std;

Scheduler::Scheduler(priority_queue<Event> *eventQueue) {
	this->eventQueue = eventQueue;
	this->isCPUIdle = true;
}

Process* Scheduler::findProcess(int procID){
	for(int i = 0; i < procTable.size(); i++){
		if(procTable[i]->procId == procID){
			return procTable[i];
		}
	}

	return NULL;
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
