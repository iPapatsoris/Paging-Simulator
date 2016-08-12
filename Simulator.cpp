#include "Simulator.h"
#include <iostream>
#include <fstream>

using namespace std;

Simulator::Simulator(const std::string& replacementAlgorithm, const int& frames, const int& frameSize,
			const int& quantum, const int& workingSetSize, const int& maxReferences) {
	this->replacementAlgorithm = replacementAlgorithm;
	this->frames = frames;
	this->frameSize = frameSize;
	this->quantum = quantum;
	this->workingSetSize = workingSetSize;
	this->maxReferences = maxReferences;
}

Simulator::~Simulator() {
	// TODO Auto-generated destructor stub
}

void Simulator::run() {
	ifstream trace1;
	ifstream trace2;
	trace1.open("bzip.trace", ios::in);
	trace2.open("gcc.trace", ios::in);
	string address; // obj

	while (this->getTrace(trace1, trace2).compare("")) {
		cout << address << endl;
	}

	trace1.close();
	trace2.close();

}

string Simulator::getTrace(ifstream& trace1, ifstream& trace2) {
	static int processId = 1;
	static int quantum = this->quantum;
	static int referenceNumber = 0;
	static istream *trace = &trace1;
	string address = ""; // change to object address

	if (referenceNumber++ == this->maxReferences || getline(*trace, address) == NULL) {
		return "";
	}
	// make address object before prossibly changing processId
	cout << address << processId;
	if (! --quantum) {
		quantum = this->quantum;
		toggleProcessId(processId); //return it first
		toggleTrace(trace, trace1, trace2);
	}
	return address;
}

void Simulator::toggleProcessId(int& processId) {
	if (processId == 1) {
		processId = 2;
	}
	else {
		processId = 1;
	}
}

void Simulator::toggleTrace(istream *trace, ifstream& trace1, ifstream& trace2) {
	if (trace == &trace1) {
		cout << "in 1" << endl;
		trace = &trace2;
	}
	else {cout << "in 2" << endl;
		trace = &trace1;
	}
	cout << trace << endl;
	cout << "trace1 " << trace1 << " trace2 " << trace2 << endl;
}

