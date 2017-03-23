/**
 * Process event implementation
 * See the corresponding header file for descriptions of each function
 */
#include "Event.h"
using namespace std;

Event::Event(EventType eventType, int eventTime, int procId) {
	this->eventType = eventType;
	this->eventTime = eventTime;
	this->procId = procId;
}

bool EventComparator::operator ()(Event *a, Event *b) {
	// The STL priority_queue considers the greatest numeric value to be the
	// highest priority, but we want the other way around
	return a->eventTime > b->eventTime;
}
