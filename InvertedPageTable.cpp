#include "InvertedPageTable.h"
#include <iostream>

using namespace std;

InvertedPageTable::InvertedPageTable(const int& frames) {
	invertedPageTableSize = frames;
	invertedPageTable = new Address *[frames];
	int frame;
	for (frame = 0 ; frame < frames ; frame++) {
		invertedPageTable[frame] = NULL;
	}
}

InvertedPageTable::~InvertedPageTable() {
	int frame;
	for (frame = 0 ; frame < invertedPageTableSize ; frame++ ) {
		if (invertedPageTable[frame] != NULL) {
			delete invertedPageTable[frame];
		}
	}
	delete[] invertedPageTable;
}

/* Return frame holding given Address, NULL if not found */
Address **InvertedPageTable::getFrameByAddress(const Address& address) {
	int frame;
	for (frame = 0 ; frame < invertedPageTableSize ; frame++ ) {
		if (invertedPageTable[frame] != NULL && invertedPageTable[frame]->equals(address)) {
			return &invertedPageTable[frame];
		}
	}
	return NULL;
}

/* Return first unoccupied frame, NULL if none found */
Address **InvertedPageTable::getFreeFrame() {
	int frame;
	for (frame = 0 ; frame < invertedPageTableSize ; frame++ ) {
		if (invertedPageTable[frame] == NULL) {
			return &invertedPageTable[frame];
		}
	}
	return NULL;
}

void InvertedPageTable::occupyFrame(Address **frame, Address *content) {
	*frame = content;
}

void InvertedPageTable::print() {
	cout << "\n~~~ InvertedPageTable ~~~\n";
	int frame;
	for (frame = 0 ; frame < invertedPageTableSize ; frame++ ) {
		if (invertedPageTable[frame] == NULL) {
			cout << "NULL" << endl;
		}
		else {
			cout << invertedPageTable[frame]->toString() << endl;
		}
	}
}

