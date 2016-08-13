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
	if (! replacementAlgorithm.compare("lru")) {
		lru = new LRU();
	}
	else if (replacementAlgorithm.compare("ws")) {
		;
	}
}

Simulator::~Simulator() {
	if (! replacementAlgorithm.compare("lru")) {
		delete lru;
	}
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

	/* Receive page requests */
	Address *address;
	while ((address = this->getTrace(trace1, trace2)) != NULL) {
		pageRequests++;
		//invertedPageTable.print();
		if (! replacementAlgorithm.compare("lru")) {
			;//lru->print();
		}
		//cout << "Trace: " << address->toString() << endl;
		Address **mappingFrame = invertedPageTable.getFrameByAddress(*address);
		if (mappingFrame != NULL) {
			/* Page already in memory */
			if (! replacementAlgorithm.compare("lru")) {
				lru->prioritize(*mappingFrame);
			}
			/* Check for 'write' request */
			if (address->getDirty() == true && (*mappingFrame)->getDirty() == false) {
				(*mappingFrame)->setDirty(true);
				cout << "Page " << address->getPageNmuber() << " from process " << address->getProcessId()
												<< " changed to dirty" << endl;
			}
			delete address;
		}
		else {
			/* Page not in memory */
			Address **freeFrame = invertedPageTable.getFreeFrame();
			if (freeFrame == NULL) {
				Address *victim;
				if (! replacementAlgorithm.compare("lru")) {
					victim = lru->getVictim();
					Address **victimFrame = invertedPageTable.getFrameByAddress(*victim);
					if (victim->getDirty()) {
						diskWrites++;
					}
					*victimFrame = address;
					lru->getRecentList().push_front(address);
				}
				pageFaults++;
				printPageFault(victim, address);
				if (victim->getDirty()) {
					cout << " Saving victim to disk";
				}
				cout << endl;

				delete victim;
			}
			else {
				invertedPageTable.occupyFrame(freeFrame, address);
				if (! replacementAlgorithm.compare("lru")) {
					lru->getRecentList().push_front(address);
				}
			}
		}
	}

	cout << "\nFrames: " << frames << "\nPage requests: " << pageRequests << "\nPage faults: " << pageFaults << "\nDisk writes: " << diskWrites << endl;
	trace1.close();
	trace2.close();

}

/* Return next page request according to parameters */
Address *Simulator::getTrace(ifstream& trace1, ifstream& trace2) {
	static int processId = 1;
	static int curQuantum = quantum;
	static int referenceNumber = 0;
	static istream *trace = &trace1;
	string line;

	if (referenceNumber++ == maxReferences || getline(*trace, line).eof()) {
		return NULL;
	}
	char *c_line = new char[line.length()+1];
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
	delete[] c_line;

	/* Switch trace between processes */
	if (! --curQuantum) {
		curQuantum = quantum;
		toggleProcessId(processId); //return it first
		toggleTrace(&trace, trace1, trace2);
	}
	return address;
}

/* Switch process */
void Simulator::toggleProcessId(int& processId) {
	if (processId == 1) {
		processId = 2;
	}
	else {
		processId = 1;
	}
}

/* Switch input */
void Simulator::toggleTrace(istream **trace, ifstream& trace1, ifstream& trace2) {
	if (*trace == &trace1) {
		*trace = &trace2;
	}
	else {
		*trace = &trace1;
	}
}

void Simulator::printPageFault(Address *victim, Address *address) {
	cout << "Page fault. Replacing page " << victim->getPageNmuber() << " from process "
			<< victim->getProcessId() << " with page " << address->getPageNmuber()
			<< " from process " << address->getProcessId() << ".";
}

