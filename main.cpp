/**
 * CS 433 Programming Assignment 3: CPU Scheduling
 * Caleb Evans, Jonathan Tapia
 * April 3, 2017
 * @description
 * This program includes several implementations of CPU scheduling algorithms,
 * as well as a Discrete Event Simulation (DES) which utilizes these algorithms.
 * @howToRun
 * Run `make` to compile the program, then run `./des.out` to execute the
 * compiled program. At startup, the program will prompt you for a load level
 * and scheduling algorithm under which to run the simulation.
 */
#include <cstdlib>
#include <iostream>
#include <queue>
#include "random.h"
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
		Event *topEvent = eventQueue->top();
		eventQueue->pop();
		delete topEvent;
	}
	delete eventQueue;
}

int main() {

	printProgramHeader();

	int currentTime = 0;

	// The total number of processes to run in the simulation
	int loadLevel = promptForLoadLevel();

	// Initialize the event queue with process arrivals at random times
	EventPriorityQueue *eventQueue = new EventPriorityQueue();
	srand(time(NULL));
	for (int i = 0; i < loadLevel; i++) {
		Event *arrivalEvent = new Event(Event::PROCESS_ARRIVAL, rand() % 300000, i);
		eventQueue->push(arrivalEvent);
	}

	SchedulerPointer *scheduler = promptForScheduler(eventQueue);

	//Main while loop
	while (!eventQueue->empty()) {
		Event *nextEvent = eventQueue->top();
		eventQueue->pop();

		currentTime = nextEvent->eventTime;
		scheduler->handleEvent(nextEvent);
		delete nextEvent;
	}
	scheduler->printStats();
	deallocateEventQueue(eventQueue);
	delete scheduler;
	return 0;
}
