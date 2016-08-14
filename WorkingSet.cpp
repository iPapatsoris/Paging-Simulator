#include "WorkingSet.h"
#include <iostream>

using namespace std;

WorkingSetManager::WorkingSetManager(const int& workingSetMaxSize) {
	workingSet = new WorkingSet *[NO_PROCESSES];
	int process;
	for (process = 0 ; process < NO_PROCESSES ; process++) {
		workingSet[process] = new WorkingSet(workingSetMaxSize);
	}
}

WorkingSetManager::~WorkingSetManager() {
	int process;
	for (process = 0 ; process < NO_PROCESSES ; process++) {
		delete workingSet[process];
	}
	delete[] workingSet;
}

WorkingSet *WorkingSetManager::getWorkingSetByProcess(const int& processId) {
	return workingSet[processId-1];
}

void WorkingSet::update(const int& pageNumber, int& victimPageNumber) {
	victimPageNumber = -1;
	if (this->recentListIsFull()) {
		victimPageNumber = recentList.front();
		recentList.pop_front();
		if (this->workingSetIsFull()) {
			if (! workingSet.erase(victimPageNumber)) {
				victimPageNumber = -1;
			}
		}
	}
	recentList.push_back(pageNumber);
	workingSet.insert(pageNumber);
}

unordered_set<int> WorkingSet::getWorkingSet() {
	return workingSet;
}

bool WorkingSet::recentListIsFull() {
	return workingSetMaxSize == recentList.size();
}

bool WorkingSet::workingSetIsFull() {
	return workingSetMaxSize == workingSet.size();
}

void WorkingSet::print() {
	cout << "\n=== Recent List === " << endl;
	for (list<int>::iterator it = recentList.begin() ; it != recentList.end() ; it++) {
		cout << (*it) << endl;
	}
	cout << "=== Working Set === " << endl;
	for (unordered_set<int>::iterator it = workingSet.begin() ; it != workingSet.end() ; it++) {
		cout << (*it) << endl;
	}

	cout << endl;
}
