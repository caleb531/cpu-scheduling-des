#include <cstdlib>
#include <iostream>
#include <queue>
#include "Event.h"
#include "SchedulerPointer.h"
#include "SchedulerFCFS.h"
#include "SchedulerSJF.h"
using namespace std;

// Print the basic program information
void printProgramHeader() {
	cout << "CS 433 CPU Scheduling DES" << endl;
	cout << "Authors: Caleb Evans, Jonathan Tapia" << endl;
	cout << endl;
}

// Prompt the user for the load level under which to run the simulation
int promptForLoadLevel() {
	cout << "Enter a load level: ";
	int loadLevel = 0;
	cin >> loadLevel;
	// Quit if the load level is invalid
	if (!loadLevel) {
		cout << "Invalid load level. Aborting." << endl;
		exit(1);
	}
	return loadLevel;
}

// Prompt the user for a scheduling algorithm under which to run the simulation
SchedulerPointer* promptForScheduler(EventPriorityQueue *eventQueue) {
	cout << "Available schedulers:" << endl;
	cout << "  1. First-Come-First-Serve (FCFS)" << endl;
	cout << "  2. Shortest-Job-First (SJF)" << endl;
	cout << "Choose a scheduler's number: ";
	int schedulerChoice;
	cin >> schedulerChoice;
	switch (schedulerChoice) {
		case 1:
			cout << "You chose FCFS" << endl;
			return new SchedulerFCFS(eventQueue);
		case 2:
			cout << "You chose SJF" << endl;
			return new SchedulerSJF(eventQueue);
		default:
			cout << "Invalid scheduler. Aborting." << endl;
			exit(1);
	}
}

// Deallocate event queue, including any events still in the queue
void deallocateEventQueue(EventPriorityQueue *eventQueue) {
	while (!eventQueue->empty()) {
		Event* topEvent = eventQueue->top();
		eventQueue->pop();
		delete topEvent;
	}
	delete eventQueue;
}

int main() {

	printProgramHeader();

	const int quitTime = 300000;
	int currentTime = 0;

	EventPriorityQueue *eventQueue = new EventPriorityQueue();

	// The total number of processes to run in the simulation
	int loadLevel = promptForLoadLevel();

	//Filling the event queue for testing purposes
	for (int i = 0; i < loadLevel; i++) {
		Event* arrivalEvent = new Event(Event::PROCESS_ARRIVAL, 0, i);
		eventQueue->push(arrivalEvent);
	}

	SchedulerPointer* scheduler = promptForScheduler(eventQueue);

	//Main while loop
	while (!eventQueue->empty() && currentTime < quitTime) {
		Event* nextEvent = eventQueue->top();
		eventQueue->pop();

		currentTime = nextEvent->eventTime;
		scheduler->handleEvent(nextEvent);
		delete nextEvent;
	}
	deallocateEventQueue(eventQueue);
	delete scheduler;
	return 0;
}
