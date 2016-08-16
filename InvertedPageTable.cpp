#include "InvertedPageTable.h"
#include <iostream>
#include <algorithm>

using namespace std;

InvertedPageTable::InvertedPageTable(const int& frames) {
	invertedPageTableSize = frames;
	invertedPageTable = new Address *[frames];
	for (int frame = 0 ; frame < frames ; frame++) {
		invertedPageTable[frame] = NULL;
	}
}

InvertedPageTable::~InvertedPageTable() {
	for (int frame = 0 ; frame < invertedPageTableSize ; frame++ ) {
		if (invertedPageTable[frame] != NULL) {
			delete invertedPageTable[frame];
		}
	}
	delete[] invertedPageTable;
}

/* Return frame holding given Address, NULL if not found */
Address **InvertedPageTable::getFrameByAddress(const Address& address) {
	for (int frame = 0 ; frame < invertedPageTableSize ; frame++ ) {
		if (invertedPageTable[frame] != NULL && invertedPageTable[frame]->equals(address)) {
			return &invertedPageTable[frame];
		}
	}
	return NULL;
}

/* Return first unoccupied frame, NULL if none found */
Address **InvertedPageTable::getFreeFrame() {
	for (int frame = 0 ; frame < invertedPageTableSize ; frame++ ) {
		if (invertedPageTable[frame] == NULL) {
			return &invertedPageTable[frame];
		}
	}
	return NULL;
}

void InvertedPageTable::occupyFrame(Address **frame, Address *content) {
	*frame = content;
}

Address **InvertedPageTable::getVictimFrameNotInSet(const list<Address>& workingSet) {
	for (int frame = 0 ; frame < invertedPageTableSize ; frame++) {
		if (find(workingSet.begin(), workingSet.end(), *invertedPageTable[frame]) == workingSet.end()) {
			return &invertedPageTable[frame];
		}
	}
	return NULL;
}


void InvertedPageTable::print() const {
	cout << "\n~~~ InvertedPageTable ~~~\n";
	for (int frame = 0 ; frame < invertedPageTableSize ; frame++ ) {
		if (invertedPageTable[frame] == NULL) {
			cout << "NULL" << endl;
		}
		else {
			cout << invertedPageTable[frame]->toString() << endl;
		}
	}
}

