#ifndef WORKINGSET_H_
#define WORKINGSET_H_

#define NO_PROCESSES 2

#include <list>
#include "Address.h"

class WorkingSet {

private:
	std::list<Address> recentList;
	std::list< Address> workingSet;
	int workingSetMaxSize;

public:
	WorkingSet(const int& workingSetMaxSize) : workingSetMaxSize(workingSetMaxSize) {}
	~WorkingSet() {}
	void update(const Address& address, Address **victimAddress);
	std::list<Address>& getWorkingSet();
	bool recentListIsFull();
	bool workingSetIsFull();
	void print();
};

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
