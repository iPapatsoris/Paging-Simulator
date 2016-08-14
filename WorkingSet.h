#ifndef WORKINGSET_H_
#define WORKINGSET_H_

#define NO_PROCESSES 2

#include <list>
#include "InvertedPageTable.h"

class WorkingSet {

private:
	std::list<Address *> workingSet;
	int workingSetMaxSize;

public:
	WorkingSet(const int& workingSetMaxSize) : workingSetMaxSize(workingSetMaxSize) {}
	~WorkingSet() {}
	void print();
};

class WorkingSetManager {
	friend class WorkingSet;

private:
	WorkingSet **workingSet;

public:
	WorkingSetManager(const int& workingSetMaxSize);
	~WorkingSetManager();
	void putInMemory(InvertedPageTable& invertedPageTable, Address *address, const bool& proccessSwitch);
};


#endif /* WORKINGSET_H_ */
