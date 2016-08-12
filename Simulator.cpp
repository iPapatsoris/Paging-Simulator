#include "Simulator.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

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

	int pageRequests = 0;
	int pageFaults = 0;
	int diskWrites = 0;
	//int diskReads = 0;

	Address *address;
	while ((address = this->getTrace(trace1, trace2)) != NULL) {
		pageRequests++;
		invertedPageTable.print();
		cout << "Trace: " << address->toString() << endl;
		Address *mappingFrame = invertedPageTable.getFrameByAddress(*address);
		if (mappingFrame != NULL) {
			if (address->getDirty() == true && mappingFrame->getDirty() == false) {
				mappingFrame->setDirty(true);
				cout << "Page " << address->getPageNmuber() << " from process " << address->getProcessId()
								<< " changed to dirty" << endl;
			}
		}
		else {
			Address **freeFrame = invertedPageTable.getFreeFrame();
			if (freeFrame == NULL) {
				cout << "Page fault" << endl;
				pageFaults++;
				delete address;
			}
			else {
				invertedPageTable.occupyFrame(freeFrame, address);
			}
		}
	}

	cout << "\nFrames: " << frames << "\nPage requests: " << pageRequests << "\nPage faults: " << pageFaults << "\nDisk writes: " << diskWrites << endl;
	trace1.close();
	trace2.close();

}

Address *Simulator::getTrace(ifstream& trace1, ifstream& trace2) {
	static int processId = 1;
	static int curQuantum = quantum;
	static int referenceNumber = 0;
	static istream *trace = &trace1;
	string line;

	if (referenceNumber++ == maxReferences || getline(*trace, line) == NULL) {
		return NULL;
	}
	char *c_line = new char(line.length()+1);
	strcpy(c_line, line.c_str());
	char *c_hexAddress = strtok(c_line, " ");
	char *c_operation = strtok(NULL, " \n\0");

	long decAddress = strtoul(c_hexAddress, NULL, 16);
	int pageNumber = decAddress / frameSize;
	int offset = decAddress % frameSize;
	bool dirty = false;
	if (*c_operation == 'W') {
		dirty = true;
	}
	Address *address = new Address(processId, pageNumber, dirty, offset);
	delete c_line;

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

