#include "WorkingSet.h"
#include <iostream>
#include <algorithm>

using namespace std;

WorkingSetManager::WorkingSetManager(const int& workingSetMaxSize) {
	workingSet = new WorkingSet *[NO_PROCESSES];
	for (int process = 0 ; process < NO_PROCESSES ; process++) {
		workingSet[process] = new WorkingSet(workingSetMaxSize);
	}
}

WorkingSetManager::~WorkingSetManager() {
	for (int process = 0 ; process < NO_PROCESSES ; process++) {
		delete workingSet[process];
	}
	delete[] workingSet;
}

WorkingSet *WorkingSetManager::getWorkingSetByProcess(const int& processId) {
	return workingSet[processId-1];
}

/* Advance working set window. If oldest page is removed, set victimAddress
 * for removal from memory by caller.
 */
void WorkingSet::update(const Address& address, Address **victimAddress) {
	if (this->recentListIsFull()) {
		*victimAddress = new Address(recentList.front()); // Oldest page
		recentList.pop_front();
		if (find(recentList.begin(), recentList.end(), **victimAddress) == recentList.end()) {
			workingSet.remove(**victimAddress);
		}
		else {
			delete *victimAddress;
			*victimAddress = NULL;
		}
	}
	/* Include newcomer */
	recentList.push_back(address);
	if (find(workingSet.begin(), workingSet.end(), address) == workingSet.end()) {
		/* No duplicates in working SET */
		workingSet.push_back(address);
	}
}

list<Address>& WorkingSet::getWorkingSet() {
	return workingSet;
}

bool WorkingSet::recentListIsFull() const {
	return workingSetMaxSize == recentList.size();
}

void WorkingSet::print() const {
	cout << "\n=== Recent List === " << endl;
	for (list<Address>::const_iterator it = recentList.begin() ; it != recentList.end() ; it++) {
		cout << (*it).toString() << endl;
	}
	cout << "=== Working Set === " << endl;
	for (list<Address>::const_iterator it = workingSet.begin() ; it != workingSet.end() ; it++) {
		cout << (*it).toString() << endl;
	}

	cout << endl;
}
