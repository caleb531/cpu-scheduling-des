/**
 * Process definition
 */
#pragma once
using namespace std;

class Process {

	public:

		Process(int procId, int arrivalTime);

		// A unique identifier for each process
		int procId;

		// All time values are in milliseconds

		// Time when the process starts in the simulation
		int arrivalTime;

		// The time the process finishes all of its work
		int finishTime;

		// Total amount of time spent in CPU burst.
		// Determined randomly at creation between 1 and 60 seconds
		int totalCPUDuration;

		// The remaining amount of time left for CPU bursts
		// When it reaches 0, process terminates
		int remainingCPUDuration;

		// Determined randomly at creation between 5 to 100 ms
		int averageCPUBurstLength;

		// Randomly determined based on averageCPUBurstLegth,
		// whenever a process is moved into the readyQueue
		int nextCPUBurstLength;

		// Total amount of time process spends in I/O
		int totalIODuration;

		// Randomly determined whenever a process finishes a CPU burst,
		// between 30 to 100 ms
		int IOBurstTime;

		// Used by scheduler to determine which process to run next
		int priority;

		// The state the process is currently in
		enum Status {
			READY,
			RUNNING,
			WAITING,
			TERMINATED
		};
		Status status;

		// Functions for computing process metrics

		int getArrivalTime();
		int getFinishTime();
		int getServiceTime();
		int getIOTime();
		int getTurnaroundTime();
		int getWaitingTime(int totalSchedulerTime);

};


// Define a custom comparator so that Process pointers can be compared in
// priority queues
class ProcessComparator {

	public:

		bool operator ()(Process *a, Process *b);

};
