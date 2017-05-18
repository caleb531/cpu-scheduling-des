# CS 433 CPU Scheduling Simulation

*Copyright 2017 Caleb Evans, Jonathan Tapia*

This program is a discrete event simulation (DES) of various CPU scheduling
algorithms, written in C++. The algorithms tested include:

- First-Come-First-Serve (FCFS)
- Shortest-Job-First (SJF)
- Round-Robin (RR)
- Preemptive-Shortest-Job-First (PSJF)

## How to run

Run `make` to compile the program, then run `./des.out` to execute the compiled
program. At startup, the program will prompt you for a load level and scheduling
algorithm under which to run the simulation.
