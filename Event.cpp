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
