#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <string>
#include <iostream>
#include <fstream>
#include "Address.h"
#include "InvertedPageTable.h"
#include "LRU.h"
#include "WorkingSet.h"
#include "Statistics.h"

class Simulator {

private:
	std::string replacementAlgorithm;
	int frames;
	int frameSize;
	int quantum;
	int workingSetSize;
	int maxReferences;
	InvertedPageTable invertedPageTable;
	LRU *lru;
	WorkingSetManager *workingSetManager;
	Statistics statistics;


public:
	Simulator(const std::string& replacementAlgorithm, const int& frames, const int& frameSize,
			const int& quantum, const int& workingSetSize, const int& maxReferences);
	~Simulator();
	void run();
	void runLRU(Address *address);
	void runWorkingSet(Address *address, bool& processSwitch);
	Address *getTrace(std::ifstream& trace1, std::ifstream& trace2, bool& processSwitch);
	void restoreWorkingSetMemory(std::list<Address>& workingSet, bool& restore);
	void static toggleProcessId(int& processId);
	void static toggleTrace(std::istream **trace, std::ifstream& trace1, std::ifstream& trace2);
	void static printPageFault(Address *victim, Address *address);
};

#endif /* SIMULATOR_H_ */
