//This program simulates the core scheduling of a tablet by using different queues and various other functions to simulate the execution of proccesses in an actual tablet.
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class core
{
private:
	int coreid; //retreice core
	int procnum;
	int clockmeister;
	string state = "free";
public:
	core(int x)
	{
		coreid = x;
		clockmeister = 0;
	}
	void setnumcores(int x, int pnum)
	{
		coreid = x;
		procnum = pnum;
	}
    bool isfree()
	{
		if (state == "free")
			return true;
		return false;
	}
	int gettime()
	{
		return clockmeister;
	}
	void setcorefree()
	{
		procnum = -1;
		state = "free";
	}
	int getprocid()
	{
		return procnum;
	}
	void setcorebusy(int x, int pnum)
	{
		procnum = pnum;
		clockmeister = x;
		state = "busy";
	}
};

struct re //1 line = 1 re. Holds info
{
private:
	string retype;
	int retime;
public:

	re(string x, int y)
	{
		retype = x;
		retime = y;
	}
	int getretime()
	{
		return retime;
	}
	string getretype()
	{
		return retype;
	}
};


class forinput
{ //for input
private:
	int clockmeister; //track how long busy
	int currentprocess; //current process
	string state = "free"; //status (free, block, ect)
public:
    int gettimer()
	{
		return clockmeister;
	}
	forinput()
	{
		clockmeister = 0;
	}
	void setfree()
	{ //set state to free
		currentprocess = -1;
		state = "free";
	}
	void setbusy(int x, int procnum) //sets state to busy
	{
		clockmeister = x;
		currentprocess = procnum;
		state = "busy";
	}
	bool isfree()//checks if free
	{
		if (state == "free")
			return true;
		return false;
	}
    int getpid() //gets process
	{
		return currentprocess;
	}
};

struct process
{ //names should explain what each does
private:
	int pid, arrivaltime;
	string status;
	vector<re> res;
public:
	process(int nid, int arrival)
	{
		pid = nid;
		arrivaltime = arrival;
	}
	string getstatus()
	{
		return status;
	}
	void print()
	{
		cout << "proces number: " << pid << "  Time arrived: " << arrivaltime << endl;
		for (unsigned int i = 0; i < res.size(); i++)
		{
			cout << res[i].getretype() << " " << res[i].getretime() << endl;;
		}
	}
	void addre(string req, int reqTime)
	{
		re temp(req, reqTime);
		res.push_back(temp);
	}
	re retreivere()
	{
		return res[0];
	}
	void delre()
	{
		res.erase(res.begin());
	}
	int retreivenum()
	{
		return pid;
	}
	bool isempty()
	{
		if (res.size() == 0)
			return true;
		else return false;
	}
	void setstatus(string x)
	{
		status = x;
	}
	void setnum(int x)
	{
		pid = x;
	}
	void settimearrive(int x)
	{
		arrivaltime = x;
	}
	int getarrivetime()
	{
		return arrivaltime;
	}
};

class Ssd//creates ssd class
{
private:
	int clockmeister;
	int procnum;
	string state = "free";
public:
	Ssd()
	{
		clockmeister = 0;
	}
	int gettime()
	{
		return clockmeister;
	}
	int getprocid()
	{
		return procnum;
	}
	void ssdfree() //sets to free state
	{
		procnum = -1;
		state = "free";
	}
	void ssdbusy(int x, int pnumber) //set to busy
	{
		clockmeister = x;
		procnum = pnumber;
		state = "busy";
	}
	bool isfree()
	{
		if (state == "free")
			return true;
		return false;
	}
};

class tab //class to simulate tablet
{
private:

	int numbercores, numberprocesses, processesStarted = -1;//numbercores = is obvjously just number of cores. Same logic can be applied to rest.
	Ssd ssd; //creating ssd object
	forinput inputs;
    queue <process> ssdqueue; //processes waiting for ssd
	queue <process> inputqueue; //processes waiting for input device
	queue <process> processtable;//process table
	queue <process> readyqueue; //processes waiting for cor
    vector<core> corestorage; //stores core
	vector<process> processstorage;
public:
	tab(int, int, vector<process>);
	void completecore(int);
	void completessd();
    void processarrive(process&);
	void completesim();
    void outputprocess(int);
    void corereqstep(process&);
    void completeinput();
	void ssdstep(process&);
	void corestat();
	void inputting(process&);
	void nextstepreq(process &);
    void completeprocess(int);
	void events();
    int freethecores();

};


int main()
{
	string word, filename;
	int number;
	int proccount = -1;
	int corecount;
	vector<process> processstorage;

	while (cin >> word && cin >> number)
	{
		if (word == "NCORES")
		{
			corecount = number;
		}
		else if (word == "NEW")
		{
			proccount++;
			process temp(proccount, number);
			processstorage.push_back(temp);
		}
		else
		{
			processstorage.back().addre(word, number);
		}
	}
	for (int i = 0; i <= proccount; i++)
	{
		processstorage[i].print();
		cout << endl;
	}
	proccount++;
	tab sys(proccount, corecount, processstorage);
	return 0;
}

int clockmeistertime = 0;
double ssdsum = 0;
double ssdtot = 0;
double accesscore = 0;

void
tab::nextstepreq(process &temp)
{
	if (temp.isempty())
	{
		completeprocess(temp.retreivenum());
		events();
		return;
	}
	re next = temp.retreivere();
	string reqType = next.getretype();
	if (reqType == "CORE")
		corereqstep(temp);
	else if (reqType == "SSD")
		ssdstep(temp);
	else if (reqType == "INPUT")
		inputting(temp);
}
void tab::completecore(int numcores)//finish core
{
	int processFinished = corestorage[numcores].getprocid();
	re del = processstorage[processFinished].retreivere();
	accesscore += del.getretime();
	processstorage[processFinished].delre();
	cout << "core completion event for process " << processFinished << " at time " << clockmeistertime << " ms" << endl;
	if (readyqueue.empty())
	{
		corestorage[numcores].setcorefree();
		cout << "core " << numcores << " is now free" << endl;
		nextstepreq(processstorage[processFinished]);
	}
	else
	{
		process temp = readyqueue.front();
		readyqueue.pop();
		re req = temp.retreivere();
		corestorage[numcores].setcorebusy(req.getretime() + clockmeistertime, temp.retreivenum());
		cout << "Process " << temp.retreivenum() << " will release a core at time " << req.getretime() + clockmeistertime << " ms " << endl;
		nextstepreq(processstorage[processFinished]);
	}
}

void tab::completessd()//finish ssd
{
	int processFinished = ssd.getprocid();
	re del = processstorage[processFinished].retreivere();
	ssdsum += del.getretime();
	ssdtot++;
	processstorage[processFinished].delre();
	cout << "Ssd completion event for process " << processFinished << " at time " << clockmeistertime << " ms" << endl;
	if (ssdqueue.empty())
	{
		cout << "Ssd is now free" << endl;
		ssd.ssdfree();
		nextstepreq(processstorage[processFinished]);
	}
	else
	{
		process temp = ssdqueue.front();
		ssdqueue.pop();
		re req = temp.retreivere();
		ssd.ssdbusy(req.getretime() + clockmeistertime, temp.retreivenum());
		cout << "Process " << temp.retreivenum() << " will release SSD at time " << req.getretime() + clockmeistertime << " ms " << endl;
		nextstepreq(processstorage[processFinished]);
	}
}

void
tab::corereqstep(process &temp) //start core
{
	int numcores = freethecores();
	re next = temp.retreivere();
	int reqTime = next.getretime();

	cout << "Pocess " << temp.retreivenum() << " requests a core at time " << clockmeistertime << " ms for " << reqTime << " ms" << endl;
	if (numcores != -1)
	{
		corestorage[numcores].setcorebusy(reqTime + clockmeistertime, temp.retreivenum());
		cout << "Process " << temp.retreivenum() << " will release a core at time  " << reqTime + clockmeistertime << endl;
		temp.setstatus("RUNNING");
	}
	else
	{
		cout << "Process " << temp.retreivenum() << " must wait for a core" << endl;
		readyqueue.push(temp);
		temp.setstatus("READY");
		cout << "Ready queue contains " << readyqueue.size() << " processes waiting for a core" << endl;
	}
	events();
}

void tab::inputting(process &temp)//begins input
{
	re next = temp.retreivere();
	int reqTime = next.getretime();
	cout << "Process " << temp.retreivenum() << " requests the input device for: " << reqTime << " ms at " << clockmeistertime << endl;
	if (inputs.isfree())
	{
		inputs.setbusy(reqTime + clockmeistertime, temp.retreivenum());
		cout << "Process " << temp.retreivenum() << " starts input at " << clockmeistertime << endl;
	}
	else
	{
		inputqueue.push(temp);
		cout << "Process " << temp.retreivenum() << " has been added to input queue for " << reqTime << endl;
	}
	temp.setstatus("BLOCKED");
	events();
}

void tab::completeinput()//tells to finish
{
	int processFinished = inputs.getpid();

	re del = processstorage[processFinished].retreivere();

	processstorage[processFinished].delre();
	cout << "Core completion event for process " << processFinished << " at time " << clockmeistertime << " ms" << endl;

	if (inputqueue.empty())
	{
		inputs.setfree();
		cout << "Input device is now free " << endl;
		nextstepreq(processstorage[processFinished]);
	}
	else
	{
		process temp = inputqueue.front();
		inputqueue.pop();
		re req = temp.retreivere();
		inputs.setbusy(req.getretime() + clockmeistertime, temp.retreivenum());
		cout << "Process " << temp.retreivenum() << " will release input device at time " << req.getretime() + clockmeistertime << " ms " << endl;
		nextstepreq(processstorage[processFinished]);
	}
}

int tab::freethecores()//returns amount of free cores
{
	for (unsigned int i = 0; i < corestorage.size(); i++)
	{
		if (corestorage[i].isfree())
			return i;
	}
	return -1;
}

void tab::corestat()
{
	for (int i = 0; i < numbercores; i++)
	{
		if (corestorage[i].isfree())
			cout << "core " << i << " is free" << endl;
		else
			cout << "core " << i << " is not free " << corestorage[i].gettime() << endl;
	}
}


void tab::completesim()//output summary
{
	cout << "Summary " << endl;
	cout << "Number of processes completed: " << processesStarted + 1 << endl;
	cout << "Total number of SSD accesses: " << ssdtot << endl;
	cout << "Average SSD access time: ";
	printf("%.2f", (ssdsum / ssdtot));
	cout << endl;
	cout << "Total elapsed time: " << clockmeistertime << " ms" << endl;
	cout << "Core Utilization: ";
	printf("%.2f", (accesscore / clockmeistertime) * 100);
	cout << " percent" << endl;
	cout << "SSD Utilization: ";
	printf("%.2f", (ssdsum / clockmeistertime) * 100);
	cout << " percent" << endl;
}


void tab::processarrive(process & temp)
{
	cout << "Arrival event for process " << temp.retreivenum() << " at time " << processstorage[temp.retreivenum()].getarrivetime() << endl;
	clockmeistertime = processstorage[temp.retreivenum()].getarrivetime();
	cout << endl;
	outputprocess(processesStarted);
	processesStarted++;
	corereqstep(temp);
}

void
tab::events()//finds next event with rpocess table
{
	int quickest = 99999999;
	int numcore;
	string event = "empty";
	process *temp;
	if (!processtable.empty())
	{
		temp = &processtable.front();
	}
	if (processesStarted + 1 < numberprocesses)
	{
		if (processstorage[processesStarted + 1].getarrivetime() < quickest)
		{
			quickest = processstorage[processesStarted + 1].getarrivetime();
			event = "arrival";
		}
	}
	for (unsigned int i = 0; i < numbercores; i++)
	{
		if (corestorage[i].isfree() == false)
		{
			if (corestorage[i].gettime() < quickest)
			{
				quickest = corestorage[i].gettime();
				event = "core";
				numcore = i;
			}
		}
	}
	if (!ssd.isfree())
	{
		if (ssd.gettime() < quickest)
		{
			quickest = ssd.gettime();
			event = "ssd";
		}
	}
	if (!inputs.isfree())
	{
		if (inputs.gettimer() < quickest)
		{
			quickest = inputs.gettimer();
			event = "input";
		}
	}
	if (event == "core")
	{
		clockmeistertime = quickest;
		completecore(numcore);
	}
	else if (event == "ssd")
	{
		clockmeistertime = quickest;
		completessd();
	}
	else if (event == "input")
	{
		clockmeistertime = quickest;
		completeinput();
	}

	else if (event == "arrival")
	{
		clockmeistertime = quickest;
		processarrive(processstorage[processesStarted + 1]);
	}
	else
	{
		completesim();
	}
}

void tab::completeprocess(int x)//outputs process status
{
	cout << endl;
	cout << "Process " << x << " terminated at time " << clockmeistertime << " ms" << endl;
	processstorage[x].setstatus("Terminated");
	for (int i = 0; i < processesStarted + 1; i++)
	{
		cout << "Process " << i << " is " << processstorage[i].getstatus() << endl;
	}
	cout << endl;
}

void tab::outputprocess(int x)
{
	cout << "Process " << x + 1 << " starts at a time " << processstorage[x + 1].getarrivetime() << " ms" << endl;
	if (x != -1)
	{
		for (int i = 0; i <= x; i++)
		{
			cout << "Process " << i << " is " << processstorage[i].getstatus() << endl;
		}
	}
	cout << endl;
}
tab::tab(int x, int y, vector<process> list)
{
	numberprocesses = x;
	numbercores = y;
	for (int i = 0; i < numbercores; i++) //start corestorage
	{
		core temp(i);
		corestorage.push_back(temp);
	}
	processstorage = list;
	events();
}

void tab::ssdstep(process &temp)//start ssd
{
	re next = temp.retreivere();
	int reqTime = next.getretime();

	cout << "Process " << temp.retreivenum() << " requests the ssd for: " << reqTime << " ms at " << clockmeistertime << endl;
	if (ssd.isfree())
	{
		ssd.ssdbusy(reqTime + clockmeistertime, temp.retreivenum());
		cout << "Process " << temp.retreivenum() << " has the SSD for " << reqTime << endl;
	}
	else
	{
		cout << "Process " << temp.retreivenum() << " has been added to SSD queue for " << reqTime << endl;
		ssdqueue.push(temp);
	}
	temp.setstatus("BLOCKED");
	events();
}
