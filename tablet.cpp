/*
Jacob Reihl 1501519
Cosc 3360
2/23
The program is to simulate a tablet with peripherals handling incoming processes and their timings.
*/

#include <iostream>
#include <queue>
#include "tablet.h"
using namespace std;

int cloccTime = 0;
double sumSSD = 0;
double totalSSD = 0;
double coreAccess = 0;

Tablet::Tablet(int x, int y, vector<process> list) {
	numProcesses = x;
	numCores = y;
	for (int i = 0; i < numCores; i++) { //initialize coresVec
		core temp(i);
		coresVec.push_back(temp);
	}
	processVec = list;
	findEvent();
}

int Tablet::freeCores() { //returns # of free cores
	for (unsigned int i = 0; i < coresVec.size(); i++) {
		if (coresVec[i].isFree())
			return i;
	}
	return -1;
}

void Tablet::printStatusOfCores() {
	for (int i = 0; i < numCores; i++) {
		if (coresVec[i].isFree())
			cout << "core " << i << " is free" << endl;
		else
			cout << "core " << i << " is busy " << coresVec[i].getTimer() << endl;
	}
}

void Tablet::findEvent() { //determines next event with process table
	int quickest = 99999999;
	int coreNUM;
	string event = "empty";
	process *temp;
	if (!processTable.empty()) {
		temp = &processTable.front();
	}
	if (processesStarted + 1 < numProcesses) {
		if (processVec[processesStarted + 1].getArrivalTime() < quickest) {
			quickest = processVec[processesStarted + 1].getArrivalTime();
			event = "arrival";
		}
	}
	for (unsigned int i = 0; i < numCores; i++) {
		if (coresVec[i].isFree() == false) {
			if (coresVec[i].getTimer() < quickest) {
				quickest = coresVec[i].getTimer();
				event = "core";
				coreNUM = i;
			}
		}
	}
	if (!ssd.isFree()) {
		if (ssd.getTimer() < quickest) {
			quickest = ssd.getTimer();
			event = "ssd";
		}
	}
	if (!inputD.isFree()) {
		if (inputD.getTimer() < quickest) {
			quickest = inputD.getTimer();
			event = "input";
		}
	}
	if (event == "core") {
		cloccTime = quickest;
		coreCompletionStep(coreNUM);
	}
	else if (event == "ssd") {
		cloccTime = quickest;
		ssdCompletionStep();
	}
	else if (event == "input") {
		cloccTime = quickest;
		inputCompletionStep();
	}

	else if (event == "arrival") {
		cloccTime = quickest;
		processArrivalStep(processVec[processesStarted + 1]);
	}
	else {
		simulationCompletionStep();
	}
}

void Tablet::nextReqStep(process &temp) { //when a req is completed call this to put process in correct place in tablet
	if (temp.empty()) {
		processCompletionStep(temp.getProcessNum());
		findEvent();
		return;
	}
	Req next = temp.getReq();
	string reqType = next.getReqType();
	if (reqType == "CORE")
		coreReqStep(temp);
	else if (reqType == "SSD")
		ssdReqStep(temp);
	else if (reqType == "INPUT")
		inputReqStep(temp);
}

void Tablet::coreReqStep(process &temp) { //call to start core
	int coreNum = freeCores();
	Req next = temp.getReq();
	int reqTime = next.getReqTime();

	cout << "-- Process " << temp.getProcessNum() << " requests a core at time " << cloccTime << " ms for " << reqTime << " ms" << endl;
	if (coreNum != -1) {
		coresVec[coreNum].setCoreBusy(reqTime + cloccTime, temp.getProcessNum());
		cout << "-- Process " << temp.getProcessNum() << " will release a core at time  " << reqTime + cloccTime << endl;
		temp.setState("RUNNING");
	}
	else {
		cout << "-- Process " << temp.getProcessNum() << " must wait for a core" << endl;
		readyQueue.push(temp);
		temp.setState("READY");
		cout << "-- Ready queue now contains " << readyQueue.size() << " processes waiting for a core" << endl;
	}
	findEvent();
}

void Tablet::ssdReqStep(process &temp) { //call to start ssd
	Req next = temp.getReq();
	int reqTime = next.getReqTime();

	cout << "-- Process " << temp.getProcessNum() << " requests the ssd for: " << reqTime << " ms at " << cloccTime << endl;
	if (ssd.isFree()) {
		ssd.setSSDbusy(reqTime + cloccTime, temp.getProcessNum());
		cout << "-- Process " << temp.getProcessNum() << " has the SSD for " << reqTime << endl;
	}
	else {
		cout << "-- Process " << temp.getProcessNum() << " has been added to SSD queue for " << reqTime << endl;
		ssdQueue.push(temp);
	}
	temp.setState("BLOCKED");
	findEvent();
}

void Tablet::inputReqStep(process &temp) { //call to start input
	Req next = temp.getReq();
	int reqTime = next.getReqTime();
	cout << "-- Process " << temp.getProcessNum() << " requests the input device for: " << reqTime << " ms at " << cloccTime << endl;
	if (inputD.isFree()) {
		inputD.setInputBusy(reqTime + cloccTime, temp.getProcessNum());
		cout << "-- Process " << temp.getProcessNum() << " starts input at " << cloccTime << endl;
	}
	else {
		inputQueue.push(temp);
		cout << "-- Process " << temp.getProcessNum() << " has been added to input queue for " << reqTime << endl;
	}
	temp.setState("BLOCKED");
	findEvent();
}

void Tablet::coreCompletionStep(int coreNum) { //call on core finish
	int processFinished = coresVec[coreNum].getProcessID();
	Req del = processVec[processFinished].getReq();
	coreAccess += del.getReqTime();
	processVec[processFinished].deleteReq();
	cout << "-- CORE completion event for process " << processFinished << " at time " << cloccTime << " ms" << endl;
	if (readyQueue.empty()) {
		coresVec[coreNum].setCoreFree();
		cout << "-- Core " << coreNum << " is now free" << endl;
		nextReqStep(processVec[processFinished]);
	}
	else {
		process temp = readyQueue.front();
		readyQueue.pop();
		Req req = temp.getReq();
		coresVec[coreNum].setCoreBusy(req.getReqTime() + cloccTime, temp.getProcessNum());
		cout << "-- Process " << temp.getProcessNum() << " will release a core at time " << req.getReqTime() + cloccTime << " ms " << endl;
		nextReqStep(processVec[processFinished]);
	}
}

void Tablet::ssdCompletionStep() { //call on ssd finish
	int processFinished = ssd.getProcessID();
	Req del = processVec[processFinished].getReq();
	sumSSD += del.getReqTime();
	totalSSD++;
	processVec[processFinished].deleteReq();
	cout << "-- SSD completion event for process " << processFinished << " at time " << cloccTime << " ms" << endl;
	if (ssdQueue.empty()) {
		cout << "-- SSD is now free" << endl;
		ssd.setSSDfree();
		nextReqStep(processVec[processFinished]);
	}
	else {
		process temp = ssdQueue.front();
		ssdQueue.pop();
		Req req = temp.getReq();
		ssd.setSSDbusy(req.getReqTime() + cloccTime, temp.getProcessNum());
		cout << "-- Process " << temp.getProcessNum() << " will release SSD at time " << req.getReqTime() + cloccTime << " ms " << endl;
		nextReqStep(processVec[processFinished]);
	}
}

void Tablet::inputCompletionStep() { //call on input device finish
	int processFinished = inputD.getProcessID();

	Req del = processVec[processFinished].getReq();

	processVec[processFinished].deleteReq();
		cout << "-- CORE completion event for process " << processFinished << " at time " << cloccTime << " ms" << endl;

	if (inputQueue.empty()) {
		inputD.setInputFree();
		cout << "-- Input device is now free " << endl;
		nextReqStep(processVec[processFinished]);
	}
	else {
		process temp = inputQueue.front();
		inputQueue.pop();
		Req req = temp.getReq();
		inputD.setInputBusy(req.getReqTime() + cloccTime, temp.getProcessNum());
		cout << "-- Process " << temp.getProcessNum() << " will release input device at time " << req.getReqTime() + cloccTime << " ms " << endl;
		nextReqStep(processVec[processFinished]);
	}
}

void Tablet::processArrivalStep(process & temp) {
	cout << "-- Arrival event for process " << temp.getProcessNum() << " at time " << processVec[temp.getProcessNum()].getArrivalTime() << endl;
	cloccTime = processVec[temp.getProcessNum()].getArrivalTime();
	cout << endl;
	printProcesses(processesStarted);
	processesStarted++;
	coreReqStep(temp);
}

void Tablet::processCompletionStep(int x) { //prints status of processes upon finishing
	cout << endl;
	cout << "Process " << x << " terminated at time " << cloccTime << " ms" << endl;
	processVec[x].setState("Terminated");
	for (int i = 0; i < processesStarted + 1; i++) {
		cout << "Process " << i << " is " << processVec[i].getState() << endl;
	}
	cout << endl;
}

void Tablet::printProcesses(int x) {
	cout << "Process " << x + 1 << " starts at a time " << processVec[x + 1].getArrivalTime() << " ms" << endl;
	if (x != -1) {
		for (int i = 0; i <= x; i++) {
			cout << "Process " << i << " is " << processVec[i].getState() << endl;
		}
	}
	cout << endl;
}

void Tablet::simulationCompletionStep() { //prints summary
	cout << "SUMMARY " << endl;
	cout << "Number of processes that completed: " << processesStarted + 1 << endl;
	cout << "Total number of SSD accesses: " << totalSSD << endl;
	cout << "Average SSD access time: ";
	printf("%.2f", (sumSSD / totalSSD));
	cout << endl;
	cout << "Total elapsed time: " << cloccTime << " ms" << endl;
	cout << "Core Utilization: ";
	printf("%.2f", (coreAccess / cloccTime) * 100);
	cout << " percent" << endl;
	cout << "SSD Utilization: ";
	printf("%.2f", (sumSSD / cloccTime) * 100);
	cout << " percent" << endl;
}