#ifndef WORKINGSET_H_
#define WORKINGSET_H_

#define NO_PROCESSES 2

#include <list>
#include <unordered_set>

class WorkingSet {

private:
	std::list<int> recentList;
	std::unordered_set<int> workingSet;
	int workingSetMaxSize;

public:
	WorkingSet(const int& workingSetMaxSize) : workingSetMaxSize(workingSetMaxSize) {}
	~WorkingSet() {}
	void update(const int& pageNumber, int& victimPageNumber);
	std::unordered_set<int> getWorkingSet();
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
