#include <iostream>
#include <queue>
#include <vector>
#include "Event.h"
#include "Scheduler.h"
#include "SchedulerFCFS.h"
#include "SchedulerSJF.h"
using namespace std;

int main() {

	cout << "Authors:" << endl;
	cout << "Caleb Evans" << endl;
	cout << "Jonathan Tapia" << endl;

	int quitTime = 300000;
	int currentTime = 0;
	int procID = 0;


	EventPriorityQueue *eventQueue = new EventPriorityQueue();


	//Filling the event queue for testing purposes
	for (int i = 0; i < 10; i++) {
		Event* arrivalEvent = new Event(Event::PROCESS_ARRIVAL, 0, procID);
		procID++;
		eventQueue->push(arrivalEvent);
	}

	SchedulerFCFS scheduler(eventQueue);

	//Main while loop
	while (!eventQueue->empty() && currentTime < quitTime) {
		Event* nextEvent = eventQueue->top();
		eventQueue->pop();

		currentTime = nextEvent->eventTime;
		scheduler.handleEvent(nextEvent);
	}
	return 0;
}
