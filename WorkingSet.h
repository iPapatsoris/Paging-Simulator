#ifndef WORKINGSET_H_
#define WORKINGSET_H_

#define NO_PROCESSES 2

#include <list>
#include "Address.h"

/* Keep a number of the most recent page requests for each process.
 * Always put each process's working set in memory before executing. */
class WorkingSet {

private:
	std::list<Address> recentList;
	std::list< Address> workingSet; // Unique elements of recentList
	int workingSetMaxSize;

public:
	WorkingSet(const int& workingSetMaxSize) : workingSetMaxSize(workingSetMaxSize) {}
	~WorkingSet() {}
	void update(const Address& address, Address **victimAddress);
	std::list<Address>& getWorkingSet();
	bool recentListIsFull() const;
	void print() const;
};

/* Working set for each process */
class WorkingSetManager {
	friend class WorkingSet;

private:
	WorkingSet **workingSet;

public:
	WorkingSetManager(const int& workingSetMaxSize);
	~WorkingSetManager();
	WorkingSet *getWorkingSetByProcess(const int& processId);
};


#endif /* WORKINGSET_H_ */
