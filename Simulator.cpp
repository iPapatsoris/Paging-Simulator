#include "Simulator.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

Simulator::Simulator(const std::string& replacementAlgorithm, const int& frames, const int& frameSize,
			const int& quantum, const int& workingSetSize, const int& maxReferences) : invertedPageTable(frames) {
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

	Address *address;
	while ((address = this->getTrace(trace1, trace2)) != NULL) {
		invertedPageTable.print();
		cout << "Trace: " << address->toString() << endl;
		Address **freeFrame = invertedPageTable.getFreeFrame();
		if (freeFrame == NULL) {
			cout << "Page fault" << endl;
			delete address;
		}
		else {
			invertedPageTable.occupyFrame(freeFrame, address);
		}
	}

	trace1.close();
	trace2.close();

}

Address *Simulator::getTrace(ifstream& trace1, ifstream& trace2) {
	static int processId = 1;
	static int curQuantum = quantum;
	static int referenceNumber = 0;
	static istream *trace = &trace1;
	string hexAddress;

	if (referenceNumber++ == maxReferences || getline(*trace, hexAddress) == NULL) {
		return NULL;
	}

	long decAddress = strtoul(hexAddress.c_str(), NULL, 16);
	int pageNumber = decAddress / frameSize;
	int offset = decAddress % frameSize;
	Address *address = new Address(processId, pageNumber, offset);

	if (! --curQuantum) {
		curQuantum = quantum;
		toggleProcessId(processId); //return it first
		toggleTrace(&trace, trace1, trace2);
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

void Simulator::toggleTrace(istream **trace, ifstream& trace1, ifstream& trace2) {
	if (*trace == &trace1) {
		*trace = &trace2;
	}
	else {
		*trace = &trace1;
	}
}

