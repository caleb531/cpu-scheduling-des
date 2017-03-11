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
