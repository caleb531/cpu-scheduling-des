/**
 * Process event definition
 */
#pragma once
using namespace std;

class Event {

	public:

		// A set of supported event types; it's public so it can be used for the
		// checking of event types in the client
		enum EventType { PROCESS_ARRIVAL, CPU_COMPLETION, IO_COMPLETION, TIMER_EXPIRATION };
		EventType eventType;

		// The time when the event should take place; it is named 'eventTime'
		// rather than 'time' so as to avoid conflicts with the standard C
		// function, time()
		int eventTime;

		// The ID of the process to which the event belongs
		int procId;

		Event(EventType eventType, int eventTime, int procId);

};

// Define a custom comparator so that Event pointers can be compared in priority
// queues
class EventComparator {

	public:

		bool operator ()(Event *a, Event *b);

};
