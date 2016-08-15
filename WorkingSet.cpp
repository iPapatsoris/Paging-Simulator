#include "WorkingSet.h"
#include <iostream>
#include <algorithm>

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

void WorkingSet::update(const Address& address, Address **victimAddress) {
	if (this->recentListIsFull()) {
		*victimAddress = new Address(recentList.front());
		recentList.pop_front();
		if (find(recentList.begin(), recentList.end(), **victimAddress) == recentList.end()) {
			workingSet.remove(**victimAddress);
		}
		else {
			delete *victimAddress;
			*victimAddress = NULL;
		}
	}
	recentList.push_back(address);
	if (find(workingSet.begin(), workingSet.end(), address) == workingSet.end()) {
		workingSet.push_back(address);
	}
}

list<Address>& WorkingSet::getWorkingSet() {
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
	for (list<Address>::iterator it = recentList.begin() ; it != recentList.end() ; it++) {
		cout << (*it).toString() << endl;
	}
	cout << "=== Working Set === " << endl;
	for (list<Address>::iterator it = workingSet.begin() ; it != workingSet.end() ; it++) {
		cout << (*it).toString() << endl;
	}

	cout << endl;
}
