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

	
	priority_queue<Event> *eventQueue = new priority_queue<Event>();


	//Fill the event queue for testing purposes
	for(int i = 0; i < 10; i++){
		Event e(Event::PROCESS_ARRIVAL, 0, procID);
		procID++;
		//cout << "Creating process arrival event" << endl;
		//cout << "pointer: " << e << endl;
		eventQueue->push(e);
	}
	
	SchedulerFCFS scheduler(eventQueue);

	/*for(int i = 0; i < eventQueue->size(); i++){
		Event *eve = eventQueue->top();
		eventQueue->pop();

		cout << "Event poped: " << eve << endl;
	}*/
	
	//Main while loop
	while(!eventQueue->empty() && currentTime < quitTime){
		cout << "Start of main while" << endl;
		Event nextEvent = eventQueue->top();
		eventQueue->pop();
		Event *ev = &nextEvent;

		currentTime = ev->eventTime;
		scheduler.handleEvent(ev);
	}

	cout << "DONE!" << endl;
	return 0;
}
