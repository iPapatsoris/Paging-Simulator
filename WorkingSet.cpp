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

void WorkingSetManager::putInMemory(InvertedPageTable& invertedPageTable, Address *address, const bool& processSwitch) {
	;
}


void WorkingSet::print() {
	cout << "=== Working Set === " << endl;
	for (list<Address *>::iterator it = workingSet.begin() ; it != workingSet.end() ; it++) {
		cout << (*it)->toString() << endl;
	}
}
