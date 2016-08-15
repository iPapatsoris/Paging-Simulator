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
	else if (! replacementAlgorithm.compare("ws")) {
		workingSetManager = new WorkingSetManager(workingSetSize);
	}
}

Simulator::~Simulator() {
	if (! replacementAlgorithm.compare("lru")) {
		delete lru;
	}
	else if (! replacementAlgorithm.compare("ws")) {
		delete workingSetManager;
	}
}

void Simulator::run() {
	ifstream trace1;
	ifstream trace2;
	trace1.open("bzip.trace", ios::in);
	trace2.open("gcc.trace", ios::in);

	bool processSwitch = false;

	/* Receive page requests */
	Address *address;
	while ((address = this->getTrace(trace1, trace2, processSwitch)) != NULL) {
		statistics.pageRequests++;
		invertedPageTable.print();
		cout << "Trace: " << address->toString() << endl;
		if (! replacementAlgorithm.compare("lru")) {
			this->runLRU(address);
		}
		else if (! replacementAlgorithm.compare("ws")) {
			this->runWorkingSet(address, processSwitch);
		}
	}
	cout << "\nFrames: " << frames << statistics.toString() << endl;
	trace1.close();
	trace2.close();

}

void Simulator::runLRU(Address *address) {
	//lru->print();
	Address **mappingFrame = invertedPageTable.getFrameByAddress(*address);
	if (mappingFrame != NULL) {
		/* Page already in memory */
		lru->prioritize(*mappingFrame);
		/* Check for 'write' request */
		if (address->getDirty() == true && (*mappingFrame)->getDirty() == false) {
			(*mappingFrame)->setDirty(true);
			cout << "Page " << address->getPageNumber() << " from process " << address->getProcessId()
																															<< " changed to dirty" << endl;
		}
		delete address;
	}
	else {
		/* Page not in memory */
		statistics.pageFaults++;
		Address **freeFrame = invertedPageTable.getFreeFrame();
		if (freeFrame == NULL) {
			Address *victim;
			victim = lru->getVictim();
			Address **victimFrame = invertedPageTable.getFrameByAddress(*victim);
			*victimFrame = address;
			lru->getRecentList().push_front(address);
			printPageFault(victim, address);
			if (victim->getDirty()) {
				cout << " Saving victim to disk.";
				statistics.diskWrites++;
			}
			cout << endl;
			delete victim;
		}
		else {
			invertedPageTable.occupyFrame(freeFrame, address);
			lru->getRecentList().push_front(address);
			printPageFault(NULL, address);
		}
	}
}

void Simulator::runWorkingSet(Address *address, bool& processSwitch) {
	WorkingSet *workingSet = workingSetManager->getWorkingSetByProcess(address->getProcessId());
	if (processSwitch) {
		cout << "Restoring process " << address->getProcessId() << " working set:" << endl;
		processSwitch = false;
		bool restore = false;
		this->restoreWorkingSetMemory(workingSet->getWorkingSet(), restore);
		if (! restore) {
			cout << "\tWorking set is already in memory" << endl;
		}
	}
	Address *victimAddress = NULL;
	workingSet->update(*address, &victimAddress);
	Address **mappingFrame = invertedPageTable.getFrameByAddress(*address);
	if (mappingFrame != NULL) {
		/* Page already in memory, check for 'write' request */
		if (address->getDirty() == true && (*mappingFrame)->getDirty() == false) {
			(*mappingFrame)->setDirty(true);
			cout << "Page " << address->getPageNumber() << " from process " << address->getProcessId()
																																	<< " changed to dirty" << endl;
		}
		delete address;
	}
	else {
		statistics.pageFaults++;
		Address **freeFrame = invertedPageTable.getFreeFrame();
		if (freeFrame != NULL) {
			invertedPageTable.occupyFrame(freeFrame, address);
			printPageFault(NULL, address);
		}
		else {
			Address **victimFrame;
			if (victimAddress != NULL) {
				victimFrame = invertedPageTable.getFrameByAddress(*victimAddress);
			}
			else {
				cout << "delete something not in set" << endl;
				victimFrame = invertedPageTable.getVictimFrameNotInSet(workingSet->getWorkingSet());
			}
			Address *toDelete = *victimFrame;
			*victimFrame = address;
			printPageFault(toDelete, address);
			if (toDelete->getDirty()) {
				cout << " Saving victim to disk.";
				statistics.diskWrites++;
			}
			cout << endl;
			delete toDelete;
		}
	}
	if (victimAddress != NULL) {
		delete victimAddress;
	}
	workingSet->print();

}

void Simulator::restoreWorkingSetMemory(std::list<Address>& workingSet, bool& restore) {
	for (list<Address>::iterator it = workingSet.begin() ; it != workingSet.end() ; it++) {
		Address **mappingFrame = invertedPageTable.getFrameByAddress(*it);
		if (mappingFrame == NULL) {
			if (! restore) {
				restore = true;
			}
			Address **victimFrame = invertedPageTable.getVictimFrameNotInSet(workingSet);
			Address *toDelete = *victimFrame;
			*victimFrame = new Address(*it);
			cout << "\t";
			printPageFault(toDelete, &(*it));
			if (toDelete->getDirty()) {
				cout << " Saving victim to disk.";
				statistics.diskWrites++;
			}
			cout << endl;
			delete toDelete;
		}
	}
}

/* Return next page request according to parameters */
Address *Simulator::getTrace(ifstream& trace1, ifstream& trace2, bool& processSwitch) {
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
	bool dirty = false;
	if (*c_operation == 'W') {
		dirty = true;
	}
	Address *address = new Address(processId, pageNumber, dirty);
	delete[] c_line;

	/* Mark start of a new process for working set restoration */
	if (curQuantum == quantum) {
		processSwitch = true;
	}

	/* Switch trace between processes */
	if (! --curQuantum) {
		curQuantum = quantum;
		toggleProcessId(processId);
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
	cout << "Page fault on requesting page " << address->getPageNumber() << " from process "
			<< address->getProcessId() << ".";
	if (victim != NULL) {
		cout << " Memory full, replacing page " << victim->getPageNumber() << " from process "
				<< victim->getProcessId() << ".";
	}
}

