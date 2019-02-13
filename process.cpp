#include "process.h"
//Everything in here pretty much does exactly what the method name suggests
//So there isnt much documentation

//empty default constructor
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
