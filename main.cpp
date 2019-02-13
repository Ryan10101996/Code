#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
using namespace std;

int clockerino = 0;
double sumSSD = 0;
double totalSSD = 0;
double coreAccess = 0;

//splits up the request type and time
vector<string> divide(string x) {
	vector<string> temp;
	string buffer;
	stringstream ss(x);

	while (ss >> buffer)
		temp.push_back(buffer);
	return temp;
}

class process {
private:
	int processNumber; //# of processes
	int arrivalTime; //process arrival time
	bool empty; //check if there are things to be processesed
	string state; //what state process is in
	vector<string> requests; //all requests in the process
public:
	process();
	process(string x);
	void setProcessNum(int);
	int getProcessNum();
	void setState(string);
	string getState();
	void setArrivalTime(int x);
	int getArrivalTime();
	void addRequest(string);
	string getRequest();
	void deleteRequest();
};

vector<string> split(string x) {
	vector<string> temp;
	string buffer;
	stringstream ss(x);
	while (ss >> buffer)
		temp.push_back(buffer);
	return temp;
}

class inputDevice {
private:
	int timer; //how long is device used
	int processNumber; //which process is using device
	string state = "free";
public:
	inputDevice() {
		timer = 0;
	}
	//-1 = no processes
	void setInputFree() {
		processNumber = -1;
		state = "free";
	}
	//Set timer to given time and log what process it is
	void setInputBusy(int x, int pN) {
		timer = x;
		processNumber = pN;
		state = "busy";
	}
	int getProcessID() {
		return processNumber;
	}
	bool isFree() {
		if (state == "free")
			return true;
		return false;
	}
	//returns when device is free
	int getTimer() {
		return timer;
	}
};


//Next 2 classes are the same as the last
//so no documentation provided, probably would have been
//better to use a template, but i'm lazy.

class SSD {
private:
	int timer;
	int processNumber;
	string state = "free";
public:
	SSD() {
		timer = 0;
	}
	int getProcessID() {
		return processNumber;
	}
	void setSSDfree() {
		processNumber = -1;
		state = "free";
	}
	void setSSDbusy(int x, int pN) {
		timer = x;
		processNumber = pN;
		state = "busy";
	}
	bool isFree() {
		if (state == "free")
			return true;
		return false;
	}
	int getTimer() {
		return timer;
	}
};

class core {
private:
	int coreID;
	int processNumber;
	int timer;
	string state = "free";
public:
	core(int x) {
		coreID = x;
		timer = 0;
	}
	void setCoreNum(int x, int pN) {
		coreID = x;
		processNumber = pN;
	}
	void setCoreBusy(int x, int pN) {
		processNumber = pN;
		timer = x;
		state = "busy";
	}
	void setCoreFree() {
		processNumber = -1;
		state = "free";
	}
	int getProcessID() {
		return processNumber;
	}
	bool isFree() {
		if (state == "free")
			return true;
		return false;
	}
	int getTimer() {
		return timer;
	}
};

class System {
private:
	//numCores = how many cores system has
	//numProcesses = how many processes are in a system
	//processesStarted = how many process have been started
	int numCores, numProcesses, processesStarted = -1;
	vector<core> coreList; //each object in the vector represents a core in the system
	vector<process> processList;
	SSD ssd;
	inputDevice inputD;
	queue <process> readyQueue; //for processes waiting on a core
	queue <process> ssdQueue; //for processes waiting on the SSD
	queue <process> inputQueue; //for processes waiting on the imput device

public:
	System(int,int,vector<process>);
	void findEvent();
	int freeCores();
	void nextRequestRoutine(process &);
	void coreRequestRoutine(process&);
	void ssdRequestRoutine(process&);
	void inputRequestRoutine(process&);
	void processArrivalRoutine(process&);
	void coreCompletionRoutine(int);
	void ssdCompletionRoutine();
	void inputCompletionRoutine();
	void proccessCompletionRoutine(int);
	void simulationCompletionRoutine();
	void printStatusOfCores();
	void printProcesses(int);
};


int main(int argc, char*argv[]) {
	string filename = argv[0,argc-1];
	ifstream file;
	file.open(filename);
	string line;
	getline(file, line);
	vector<string> first = split(line);
	vector<process> list(10);
	int processNum = -1;
	while (getline(file, line)) {
		if (line.substr(0, 3) == "NEW") {
			processNum++;
			vector<string> temp = split(line);
			list[processNum].setArrivalTime(stoi(temp[1]));
			list[processNum].setProcessNum(processNum);
		}
		else {
			list[processNum].addRequest(line);
		}
	}
	System simulation(processNum + 1,stoi(first[1]), list);
	return 0;
}

process::process() {}
process::process(string x) {
	requests.push_back(x);
}
//returns next req
string process::getRequest() {
	if (requests.size() != 0)
		return requests[0];
	else return "no requests";
}
//used at file read
void process::addRequest(string x) {
	requests.push_back(x);
}
void process::deleteRequest() {
	requests.erase(requests.begin());
}
void process::setProcessNum(int x) {
	processNumber = x;
}
int process::getProcessNum() {
	return processNumber;
}
void process::setState(string x) {
	state = x;
}
string process::getState() {
	return state;
}
int process::getArrivalTime() {
	return arrivalTime;
}
void process::setArrivalTime(int x) {
	arrivalTime = x;
}

System::System(int x ,int y,vector<process> list) {
	numCores = y;
	numProcesses = x;
	//set up coreList based on # of cores
	for (int i = 0; i < numCores; i++) {
		core temp(i);
		coreList.push_back(temp);
	}
	//set up processList
	for (unsigned int i = 0; i < x; i++) {
		processList.push_back(list[i]);
	}
	findEvent();
}
void System::printStatusOfCores() {
	for (int i = 0; i < numCores; i++) {
		if (coreList[i].isFree())
			cout << "core " << i<< " is free" << endl;
		else
			cout << "core " << i << " is busy " << coreList[i].getTimer() << endl;
	}
}
int System::freeCores() {
	for (unsigned int i = 0; i < coreList.size(); i++) {
		if (coreList[i].isFree())
			return i;
	}
	return -1;
}
//find next event
void System::findEvent() {
	int quickest = 99999999;
	int coreNUM;
	string event = "empty";
	if (processesStarted + 1 < numProcesses) {
		if (processList[processesStarted + 1].getArrivalTime() < quickest) {
			quickest = processList[processesStarted + 1].getArrivalTime();
			event = "arrival";
		}
	}
	for (unsigned int i = 0; i < numCores; i++) {
		if (coreList[i].isFree() == false) {
			if (coreList[i].getTimer() < quickest) {
				quickest = coreList[i].getTimer();
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
		clockerino = quickest;
		coreCompletionRoutine(coreNUM);
	}
	else if (event == "ssd") {
		clockerino = quickest;
		ssdCompletionRoutine();
	}
	else if (event == "input") {
		clockerino = quickest;
		inputCompletionRoutine();
	}

	else if (event == "arrival") {

		clockerino = quickest;
		processArrivalRoutine(processList[processesStarted + 1]);
	}
	else {
		simulationCompletionRoutine();
	}
}
//if a request is completed this is called so the process is put in the right place in system
void System::nextRequestRoutine(process &temp) {
	vector<string> request = divide(temp.getRequest());
	if (request[0] == "CORE")
		coreRequestRoutine(temp);
	else if (request[0] == "SSD")
		ssdRequestRoutine(temp);
	else if (request[0] == "INPUT")
		inputRequestRoutine(temp);
	else {
		proccessCompletionRoutine(temp.getProcessNum());
		findEvent();
	}
}
//next few methods just request a part of the system
void System::coreRequestRoutine(process &temp) {
	int coreNum = freeCores();
	vector<string> request = divide(temp.getRequest());
	cout << "-- Process " << temp.getProcessNum() << " requests a core at time " <<
	clockerino  << " ms for " << request[1] << " ms" << endl;
	if (coreNum != -1) {
		coreList[coreNum].setCoreBusy(stoi(request[1]) +  clockerino,temp.getProcessNum());
		cout << "-- Process " << temp.getProcessNum() << " will release a core at time  " << stoi(request[1]) + clockerino << endl;
		temp.setState("RUNNING");
	}
	else {
		cout << "-- Process " << temp.getProcessNum() << " must wait for a core" << endl;
		readyQueue.push(temp);
		temp.setState("READY");
		cout << "-- Ready queue now contains " << readyQueue.size() << " process(es) waiting for a core" << endl;
	}
	findEvent();
}
void System::ssdRequestRoutine(process &temp) {
	vector<string> request = divide(temp.getRequest());
	cout << "-- Process " << temp.getProcessNum() << " requests the ssd for: " << request[1] << " ms at " << clockerino << endl;
	if (ssd.isFree()) {
		ssd.setSSDbusy(stoi(request[1]) + clockerino, temp.getProcessNum());
		cout << "-- Process " << temp.getProcessNum() << " has the SSD for " << request[1] << endl;
	}
	else {
		cout << "-- Process " << temp.getProcessNum() << " has been added to SSD queue for " << request[1] << endl;
		ssdQueue.push(temp);
	}
	temp.setState("BLOCKED");
	findEvent();
}
void System::inputRequestRoutine(process &temp) {
	vector<string> request = divide(temp.getRequest());
	cout << "-- Process " << temp.getProcessNum() << " requests the input device for: " << request[1] << " ms at " << clockerino << endl;
	if (inputD.isFree()) {
		inputD.setInputBusy(stoi(request[1]) + clockerino, temp.getProcessNum());
		cout << "-- Process " << temp.getProcessNum() << " starts input at " << clockerino << endl;
	}
	else {
		inputQueue.push(temp);
		cout << "-- Process " << temp.getProcessNum() << " has been added to input queue for " << request[1] << endl;
	}
	temp.setState("BLOCKED");
	findEvent();
}
//next few methods handle completion of processes
void System::coreCompletionRoutine(int coreNum) {
	int processFinished = coreList[coreNum].getProcessID();

	vector<string> del = divide(processList[processFinished].getRequest());
	coreAccess += stoi(del[1]);

	processList[processFinished].deleteRequest();

	cout << "-- CORE completion event for process " << processFinished << " at time " << clockerino << " ms" << endl;
	if (readyQueue.empty()) {
		coreList[coreNum].setCoreFree();
		cout << "-- Core " << coreNum << " is now free" << endl;
		nextRequestRoutine(processList[processFinished]);
	}
	else {
		process temp = readyQueue.front();
		readyQueue.pop();
		vector<string> request = divide(temp.getRequest());
		coreList[coreNum].setCoreBusy(stoi(request[1]) + clockerino,temp.getProcessNum());
		cout << "-- Process "<< temp.getProcessNum() << " will release a core at time " << stoi(request[1]) + clockerino << " ms " << endl;
		nextRequestRoutine(processList[processFinished]);
	}
}
void System::ssdCompletionRoutine() {
	int processFinished = ssd.getProcessID();

	vector<string> del = divide(processList[processFinished].getRequest());
	sumSSD += stoi(del[1]);
	totalSSD++;

	processList[processFinished].deleteRequest();
	cout << "-- SSD completion event for process " << processFinished << " at time " << clockerino << " ms" << endl;

	if (ssdQueue.empty()) {
		cout << "-- SSD is now free" << endl;
		ssd.setSSDfree();
		nextRequestRoutine(processList[processFinished]);
	}
	else {
		process temp = ssdQueue.front();
		ssdQueue.pop();
		vector<string> request = divide(temp.getRequest());
		ssd.setSSDbusy(stoi(request[1]) + clockerino,temp.getProcessNum());
		cout << "-- Process " << temp.getProcessNum() << " will release SSD at time " << stoi(request[1]) + clockerino << " ms " << endl;
		nextRequestRoutine(processList[processFinished]);
	}
}
void System::inputCompletionRoutine() {
	int processFinished = inputD.getProcessID();
	processList[processFinished].deleteRequest();
	cout << "-- CORE completion event for process " << processFinished << " at time " << clockerino << " ms" << endl;

	if (inputQueue.empty()) {
		inputD.setInputFree();
		cout << "-- Input device is now free " << endl;
		nextRequestRoutine(processList[processFinished]);
	}
	else {
		process temp = inputQueue.front();
		inputQueue.pop();
		vector<string> request = divide(temp.getRequest());
		inputD.setInputBusy(stoi(request[1]) + clockerino, temp.getProcessNum());
		cout << "-- Process " << temp.getProcessNum() << " will release input device at time " << stoi(request[1]) + clockerino << " ms " << endl;
		nextRequestRoutine(processList[processFinished]);
	}
}
void System::processArrivalRoutine(process & temp) {
	cout << "-- Arrival event for process "<< temp.getProcessNum() <<" at time " << processList[temp.getProcessNum()].getArrivalTime() << endl;
	clockerino = processList[temp.getProcessNum()].getArrivalTime();
	cout << endl;
	printProcesses(processesStarted);
	processesStarted++;
	coreRequestRoutine(temp);
}
void System::proccessCompletionRoutine(int x) {
	cout << endl;
	cout << "Process " << x << " terminated at time " << clockerino << " ms" << endl;
	processList[x].setState("Terminated");
	for (int i = 0; i < processesStarted + 1; i++) {
		cout << "Process " << i << " is " << processList[i].getState() << endl;
	}
	cout << endl;
}
void System::simulationCompletionRoutine() {
	cout << "SUMMARY " << endl;
	cout << "Number of processes that completed: " << processesStarted + 1 << endl;
	cout << "Total number of SSD accesses: " << totalSSD << endl;
	cout << "Average SSD access time: ";
	printf("%.2f", (sumSSD / totalSSD));
	cout << endl;
	cout << "Total elapsed time: " << clockerino << " ms" << endl;
	cout << "Core Utilization: ";
	printf("%.2f", (coreAccess / clockerino) * 100);
	cout << " percent" << endl;
	cout << "SSD Utilization: ";
	printf("%.2f", (sumSSD / clockerino) * 100);
	cout << " percent" << endl;
}
//prints out status of previous processes on arrival
void System::printProcesses(int x) {
	cout << "Process " << x + 1 << " starts at a time " << processList[x + 1].getArrivalTime() << " ms" << endl;
	if (x != -1) {
		for (int i = 0; i <= x; i++) {
			cout << "Process " << i << " is " << processList[i].getState() << endl;
		}
	}
	cout << endl;
}

