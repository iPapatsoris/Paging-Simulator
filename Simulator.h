#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <string>
#include <iostream>
#include <fstream>
#include "Address.h"
#include "InvertedPageTable.h"
#include "LRU.h"

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


public:
	Simulator(const std::string& replacementAlgorithm, const int& frames, const int& frameSize,
			const int& quantum, const int& workingSetSize, const int& maxReferences);
	~Simulator();
	void run();
	Address *getTrace(std::ifstream& trace1, std::ifstream& trace2);
	void static toggleProcessId(int& processId);
	void static toggleTrace(std::istream **trace, std::ifstream& trace1, std::ifstream& trace2);
};

#endif /* SIMULATOR_H_ */
